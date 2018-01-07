#include <netdb.h>
#include <unistd.h>
#include <cstring>
#include "TcpClient.h"

#define INVALID_DESCRIPTOR (-1)
#define TCP_PORT_MIN (1)
#define TCP_PORT_MAX (65535)

namespace Flix {

TcpClient::TcpClient():
    descriptor(INVALID_DESCRIPTOR)
{
}

TcpClient::~TcpClient()
{
    disconnect();
}

void TcpClient::connect(const std::string& host, int port)
{
    disconnect();

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
    return
        descriptor;
}

bool TcpClient::withinRange(int value, int min, int max) const
{
    return
        value >= min &&
        value <= max;
}

} /* namespace Flix */
