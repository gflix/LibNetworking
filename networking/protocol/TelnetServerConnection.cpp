#include <cstring>
#include <networking/utils/Log.h>
#include <networking/protocol/TelnetServerConnection.h>

#define TELNET_STREAM_BUFFER (128)

namespace Flix {

TelnetServerConnection::TelnetServerConnection(
    int descriptor,
    const std::string& peerAddress,
    const std::string& prompt,
    const std::string& welcomeMessage):
    GenericThread("TelnetServerConnection(" + peerAddress + ")"),
    descriptor(descriptor),
    peerAddress(peerAddress),
    prompt(prompt),
    welcomeMessage(welcomeMessage)
{
}

TelnetServerConnection::~TelnetServerConnection()
{
}

bool TelnetServerConnection::setup(void)
{
    send("\r\n");
    sendWelcomeMessage();
    send("\r\n");
    send("\r\n");
    sendPrompt();
    return true;
}

bool TelnetServerConnection::task(const Select& select)
{
    if (!select.readDescriptorIsSet(descriptor))
    {
        return true;
    }

    char buffer[TELNET_STREAM_BUFFER];
    bzero(buffer, sizeof(buffer));

    ssize_t bytesRead = ::read(descriptor, buffer, sizeof(buffer));
    if (bytesRead <= 0)
    {
        closeConnection();
        threadFinished = true;
        return true;
    }

    LOG_INFO("Received " << bytesRead << " bytes from telnet socket.");
    return true;
}

void TelnetServerConnection::updateDescriptors(Select& select)
{
    select.addReadDescriptor(descriptor);
}

void TelnetServerConnection::closeConnection(void)
{
    if (descriptor < 0) {
        return;
    }

    close(descriptor);
    descriptor = -1;
}

void TelnetServerConnection::send(const std::string& message)
{
    ssize_t bytesWritten = ::write(descriptor, message.c_str(), message.size());
    if (bytesWritten < 0)
    {
        closeConnection();
        threadFinished = true;
    }
}

void TelnetServerConnection::sendPrompt(void)
{
    send(prompt);
}

void TelnetServerConnection::sendWelcomeMessage(void)
{
    send(welcomeMessage);
}

} /* namespace Flix */
