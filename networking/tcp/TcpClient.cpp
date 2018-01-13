#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include <memory>
#include "../Select.h"
#include "TcpClient.h"

#define INVALID_DESCRIPTOR (-1)
#define TCP_PORT_MIN (1)
#define TCP_PORT_MAX (65535)
#define SOCKET_READ_TIMEOUT_MICROSECS (100000)
#define SOCKET_WRITE_TIMEOUT_MICROSECS (100000)

namespace Flix {

TcpClient::TcpClient():
    descriptor(INVALID_DESCRIPTOR)
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
        throw std::string("invalid arguments");
    }

    addrinfo getAddrInfoHints;
    addrinfo* getAddrInfoResult = nullptr;
    addrinfo* addressInfo = nullptr;

    bzero(&getAddrInfoHints, sizeof(getAddrInfoHints));
    getAddrInfoHints.ai_family = AF_UNSPEC;
    getAddrInfoHints.ai_socktype = SOCK_STREAM;

    if (getaddrinfo(host.c_str(), std::to_string(port).c_str(), &getAddrInfoHints, &getAddrInfoResult) != 0)
    {
        throw std::string("could not resolve host");
    }

    for (addressInfo = getAddrInfoResult; addressInfo; addressInfo = addressInfo->ai_next)
    {
        descriptor = socket(addressInfo->ai_family, addressInfo->ai_socktype, addressInfo->ai_protocol);
        if (descriptor <= INVALID_DESCRIPTOR)
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
        throw std::string("could not connect to host");
    }
}

void TcpClient::disconnect(void)
{
    if (isConnected())
    {
        ::close(descriptor);
        descriptor = INVALID_DESCRIPTOR;
    }
}

bool TcpClient::isConnected(void) const
{
    return
        descriptor > INVALID_DESCRIPTOR;
}

int TcpClient::getDescriptor(void) const
{
    if (!isConnected())
    {
        throw std::string("not connected");
    }

    return
        descriptor;
}

void TcpClient::send(const std::string& data) const
{
    if (!isConnected())
    {
        throw std::string("not connected");
    }

    Select select;
    select.addWriteDescriptor(descriptor);
    select.setTimeout(0, SOCKET_WRITE_TIMEOUT_MICROSECS);

    if (select.execute() <= 0)
    {
        throw std::string("could not write to socket");
    }

    size_t dataSize = data.size();
    ssize_t bytesWritten = write(descriptor, data.c_str(), data.size());

    if (dataSize != bytesWritten)
    {
        throw std::string("could not write to socket");
    }
}

void TcpClient::receive(std::string& data, size_t bufferSize) const
{
    if (!isConnected())
    {
        throw std::string("not connected");
    }

    Select select;
    select.addReadDescriptor(descriptor);
    select.setTimeout(0, SOCKET_READ_TIMEOUT_MICROSECS);

    if (select.execute() <= 0)
    {
        throw std::string("read from socket timed out");
    }

    std::unique_ptr<char> buffer { static_cast<char*>(malloc(bufferSize)) };
    ssize_t bytesRead = read(descriptor, buffer.get(), bufferSize);

    data = std::move(std::string(buffer.get(), bytesRead));
}

bool TcpClient::withinRange(int value, int min, int max) const
{
    return
        value >= min &&
        value <= max;
}

} /* namespace Flix */
