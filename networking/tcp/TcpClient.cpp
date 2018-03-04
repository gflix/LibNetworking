#include <netdb.h>
#include <cstring>
#include <memory>
#include <stdexcept>
#include <networking/tcp/TcpClient.h>

namespace Flix {

TcpClient::TcpClient():
    GenericTcpConnection()
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

} /* namespace Flix */
