#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <memory>
#include <stdexcept>
#include <networking/Select.h>
#include <networking/tcp/TcpClient.h>

#define SOCKET_READ_TIMEOUT_MICROSECS (100000)
#define SOCKET_WRITE_TIMEOUT_MICROSECS (100000)

namespace Flix {

TcpClient::TcpClient():
    GenericTcp()
{
}

TcpClient::~TcpClient()
{
    disconnect();
}

void TcpClient::connect(std::string host, int port)
{
    disconnect();

    size_t colonPosition = host.find_last_of(':');
    if (colonPosition != std::string::npos)
    {
        port = std::stoi(host.substr(colonPosition + 1), nullptr, 10);
        host.erase(colonPosition);
    }

    if (host.empty() || !withinRange(port, TCP_PORT_MIN, TCP_PORT_MAX))
    {
        throw std::invalid_argument("invalid arguments");
    }

    addrinfo getAddrInfoHints;
    addrinfo* getAddrInfoResult = nullptr;
    addrinfo* addressInfo = nullptr;

    bzero(&getAddrInfoHints, sizeof(getAddrInfoHints));
    getAddrInfoHints.ai_family = AF_UNSPEC;
    getAddrInfoHints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(host.c_str(), std::to_string(port).c_str(), &getAddrInfoHints, &getAddrInfoResult) != 0)
    {
        throw std::runtime_error("could not resolve host");
    }

    for (addressInfo = getAddrInfoResult; addressInfo; addressInfo = addressInfo->ai_next)
    {
        descriptor = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
        if (descriptor <= TCP_INVALID_DESCRIPTOR)
        {
            continue;
        }
        if (::connect(descriptor, addressInfo->ai_addr, addressInfo->ai_addrlen) != 0)
        {
            disconnect();
            continue;
        }
        break;
    }
    freeaddrinfo(getAddrInfoResult);

    if (!isConnected())
    {
        throw std::runtime_error("could not connect to host");
    }
}

void TcpClient::disconnect(void)
{
    if (isConnected())
    {
        ::close(descriptor);
        descriptor = TCP_INVALID_DESCRIPTOR;
    }
}

void TcpClient::send(const std::string& data) const
{
    if (!isConnected())
    {
        throw std::runtime_error("not connected");
    }

    Select select;
    select.addWriteDescriptor(descriptor);
    select.setTimeout(0, SOCKET_WRITE_TIMEOUT_MICROSECS);

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

void TcpClient::receive(std::string& data, size_t bufferSize) const
{
    if (!isConnected())
    {
        throw std::runtime_error("not connected");
    }

    Select select;
    select.addReadDescriptor(descriptor);
    select.setTimeout(0, SOCKET_READ_TIMEOUT_MICROSECS);

    if (select.execute() <= 0)
    {
        throw std::runtime_error("read from socket timed out");
    }

    std::unique_ptr<char> buffer { static_cast<char*>(malloc(bufferSize)) };
    ssize_t bytesRead = read(descriptor, buffer.get(), bufferSize);

    data = std::move(std::string(buffer.get(), bytesRead));
}

} /* namespace Flix */
