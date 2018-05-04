#include <arpa/inet.h>
#include <cstring>
#include <networking/utils/Log.h>
#include <networking/protocol/TelnetServer.h>

namespace Flix {

TelnetServer::TelnetServer(int port, Protocol protocol, const std::string& defaultPrompt):
    GenericThread("TelnetServer"),
    port(port),
    protocol(protocol),
    defaultPrompt(defaultPrompt)
{
}

TelnetServer::~TelnetServer()
{
}

void TelnetServer::setDefaultPrompt(const std::string& defaultPrompt)
{
    this->defaultPrompt = defaultPrompt;
}

void TelnetServer::setWelcomeMessage(const std::string& welcomeMessage)
{
    this->welcomeMessage = welcomeMessage;
}

bool TelnetServer::setup(void)
{
    try
    {
        tcpServer.start(port, protocol);
    }
    catch (std::exception& e)
    {
        LOG_ERROR("Could not start telnet server on port " << port << " (" << e.what() << ")");
        return false;
    }
    return true;
}

bool TelnetServer::task(const Select& select)
{
    if (!select.readDescriptorIsSet(tcpServer.getDescriptor()))
    {
        return true;
    }

    TelnetServerConnection* connectionThread = nullptr;
    if (protocol == Protocol::IPV4)
    {
        sockaddr_in clientAddress;
        unsigned int clientAddressSize = sizeof(clientAddress);
        int clientDescriptor = accept(tcpServer.getDescriptor(), (sockaddr*) &clientAddress, &clientAddressSize);
        if (clientDescriptor >= 0)
        {
            char clientIpAddressBuffer[INET_ADDRSTRLEN];
            bzero(clientIpAddressBuffer, sizeof(clientIpAddressBuffer));
            inet_ntop(AF_INET, &clientAddress.sin_addr, clientIpAddressBuffer, sizeof(clientIpAddressBuffer));
            std::string clientIpAddress =
                std::string(clientIpAddressBuffer) + ':' + std::to_string(ntohs(clientAddress.sin_port));

            connectionThread =
                new TelnetServerConnection(clientDescriptor, clientIpAddress, defaultPrompt, welcomeMessage);
        }
    }
    else if (protocol == Protocol::IPV6)
    {
        sockaddr_in6 clientAddress;
        unsigned int clientAddressSize = sizeof(clientAddress);
        int clientDescriptor = accept(tcpServer.getDescriptor(), (sockaddr*) &clientAddress, &clientAddressSize);
        if (clientDescriptor >= 0)
        {
            char clientIpAddressBuffer[INET6_ADDRSTRLEN];
            bzero(clientIpAddressBuffer, sizeof(clientIpAddressBuffer));
            inet_ntop(AF_INET6, &clientAddress.sin6_addr, clientIpAddressBuffer, sizeof(clientIpAddressBuffer));
            std::string clientIpAddress =
                std::string(clientIpAddressBuffer) + ':' + std::to_string(ntohs(clientAddress.sin6_port));

            connectionThread =
                new TelnetServerConnection(clientDescriptor, clientIpAddress, defaultPrompt, welcomeMessage);
        }
    }

    if (connectionThread && connectionThread->start()) {
        connectionThreads.push_back(connectionThread);
    }


    auto checkConnectionThread = connectionThreads.begin();
    while (checkConnectionThread != connectionThreads.end()) {
        if (!(*checkConnectionThread)) {
            checkConnectionThread = connectionThreads.erase(checkConnectionThread);
            continue;
        }
        if ((*checkConnectionThread)->threadHasFinished()) {
            (*checkConnectionThread)->stop();
            delete *checkConnectionThread;
            checkConnectionThread = connectionThreads.erase(checkConnectionThread);
            continue;
        }
        ++checkConnectionThread;
    }

    return true;
}

void TelnetServer::updateDescriptors(Select& select)
{
    select.addReadDescriptor(tcpServer.getDescriptor());
}

} /* namespace Flix */
