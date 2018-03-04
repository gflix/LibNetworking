#include <unistd.h>
#include <netinet/in.h>
#include <cstring>
#include <stdexcept>
#include <networking/tcp/TcpServer.h>

namespace Flix {

TcpServer::TcpServer():
    GenericTcp()
{
}

TcpServer::~TcpServer()
{
    stop();
}

void TcpServer::start(int port, Protocol procotol)
{
    stop();

    if (!withinRange(port, TCP_PORT_MIN, TCP_PORT_MAX))
    {
        throw std::invalid_argument("invalid port number");
    }

    int socketNamespace = AF_UNSPEC;
    switch (procotol)
    {
    case Protocol::IPV4:
        socketNamespace = AF_INET;
        break;
    case Protocol::IPV6:
        socketNamespace = AF_INET6;
        break;
    default:
        throw std::invalid_argument("invalid protocol");
    }

    descriptor = socket(socketNamespace, SOCK_STREAM, 0);
    if (descriptor <= TCP_INVALID_DESCRIPTOR)
    {
        throw std::runtime_error("could not create socket");
    }

    int enableReuseAddress = 1;
    setsockopt(descriptor, SOL_SOCKET, SO_REUSEADDR, &enableReuseAddress, sizeof(enableReuseAddress));

    if (procotol == Protocol::IPV4)
    {
        sockaddr_in serverAddress;
        bzero(&serverAddress, sizeof(serverAddress));
        serverAddress.sin_family = AF_INET;
        serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
        serverAddress.sin_port = htons(port);
        if (bind(descriptor, (sockaddr*) &serverAddress, sizeof(serverAddress)) != 0)
        {
            throw std::runtime_error("could not bind to socket");
        }
    }
    else
    {
        sockaddr_in6 serverAddress;
        bzero(&serverAddress, sizeof(serverAddress));
        serverAddress.sin6_family = AF_INET6;
        serverAddress.sin6_addr = in6addr_any;
        serverAddress.sin6_port = htons(port);
        if (bind(descriptor, (sockaddr*) &serverAddress, sizeof(serverAddress)) != 0)
        {
            throw std::runtime_error("could not bind to socket");
        }
    }

    if (listen(descriptor, 5) != 0)
    {
        throw std::runtime_error("could not listen on socket");
    }
}

void TcpServer::stop(void)
{
    if (isConnected())
    {
        ::close(descriptor);
        descriptor = TCP_INVALID_DESCRIPTOR;
    }
}

} /* namespace Flix */
