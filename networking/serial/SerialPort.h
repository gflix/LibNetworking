#ifndef NETWORKING_SERIAL_SERIALPORT_H_
#define NETWORKING_SERIAL_SERIALPORT_H_

#include <string>
#include <networking/serial/Baudrate.h>

#define SERIAL_RECEIVE_BUFFER_SIZE_DEFAULT (128)

namespace Flix {

class SerialPort {
public:
    SerialPort();
    virtual ~SerialPort();

    void open(const std::string& device, Baudrate baudrate);
    void close(void);

    void send(const std::string& data) const;
    void receive(std::string& data, size_t bufferSize = SERIAL_RECEIVE_BUFFER_SIZE_DEFAULT) const;

    bool isOpened(void) const;
    int getDescriptor(void) const;

protected:
    int descriptor;
};

} /* namespace Flix */

#endif /* NETWORKING_SERIAL_SERIALPORT_H_ */
