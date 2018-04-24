#include <fcntl.h>
#include <termios.h>
#include <unistd.h>
#include <cstring>
#include <memory>
#include <stdexcept>
#include <networking/Select.h>
#include <networking/serial/SerialPort.h>

#define SERIAL_INVALID_DESCRIPTOR (-1)
#define PORT_READ_TIMEOUT_MICROSECS (200000)
#define PORT_WRITE_TIMEOUT_MICROSECS (500000)


namespace Flix {

SerialPort::SerialPort():
    descriptor(SERIAL_INVALID_DESCRIPTOR)
{
}

SerialPort::~SerialPort()
{
    close();
}

void SerialPort::open(const std::string& device, Baudrate baudrate)
{
    close();

    descriptor = ::open(device.c_str(), O_RDWR);
    if (descriptor < 0)
    {
        close();
        throw std::runtime_error("could not open device \"" + device + "\"");
    }

    termios terminalSettings;
    bzero(&terminalSettings, sizeof(terminalSettings));

    terminalSettings.c_cflag = CS8 | CREAD | CLOCAL;
    terminalSettings.c_cc[VMIN] = 1;
    terminalSettings.c_cc[VTIME] = 5;
    cfsetspeed(&terminalSettings, baudrateToInt(baudrate));

    if (tcsetattr(descriptor, TCSANOW, &terminalSettings) < 0)
    {
        close();
        throw std::runtime_error("could set device attributes to \"" + device + "\"");
    }
}

void SerialPort::close(void)
{
    if (isOpened())
    {
        ::close(descriptor);
        descriptor = SERIAL_INVALID_DESCRIPTOR;
    }
}

void SerialPort::send(const std::string& data) const
{
    if (!isOpened())
    {
        throw std::runtime_error("port not opened");
    }

    Select select;
    select.addWriteDescriptor(descriptor);
    select.setTimeout(0, PORT_WRITE_TIMEOUT_MICROSECS);

    if (select.execute() <= 0)
    {
        throw std::runtime_error("could not write to socket");
    }

    size_t dataSize = data.size();
    ssize_t bytesWritten = write(descriptor, data.c_str(), data.size());

    if (dataSize != bytesWritten)
    {
        throw std::runtime_error("could not write to socket");
    }
}

void SerialPort::receive(std::string& data, size_t bufferSize) const
{
    if (!isOpened())
    {
        throw std::runtime_error("port not opened");
    }

    Select select;
    select.addReadDescriptor(descriptor);
    select.setTimeout(0, PORT_READ_TIMEOUT_MICROSECS);

    if (select.execute() <= 0)
    {
        throw std::runtime_error("read from socket timed out");
    }

    std::unique_ptr<char> buffer { static_cast<char*>(malloc(bufferSize)) };
    ssize_t bytesRead = read(descriptor, buffer.get(), bufferSize);

    data = std::move(std::string(buffer.get(), bytesRead));
}

bool SerialPort::isOpened(void) const
{
    return
        descriptor != SERIAL_INVALID_DESCRIPTOR;
}

int SerialPort::getDescriptor(void) const
{
    return
        descriptor;
}

} /* namespace Flix */
