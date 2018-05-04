#ifndef NETWORKING_PROTOCOL_TELNETSERVERCONNECTION_H_
#define NETWORKING_PROTOCOL_TELNETSERVERCONNECTION_H_

#include <vector>
#include <networking/utils/GenericThread.h>

namespace Flix {

class TelnetServerConnection: public GenericThread {
public:
    TelnetServerConnection(
        int descriptor,
        const std::string& peerAddress,
        const std::string& prompt,
        const std::string& welcomeMessage);
    virtual ~TelnetServerConnection();

protected:
    virtual bool setup(void) override;
    virtual bool task(const Select& select) override;
    virtual void updateDescriptors(Select& select) override;

private:
    int descriptor;
    std::string peerAddress;
    std::string prompt;
    std::string welcomeMessage;

    void closeConnection(void);
    void send(const std::string& message);
    void sendPrompt(void);
    void sendWelcomeMessage(void);
};

typedef std::vector<TelnetServerConnection*> TelnetServerConnections;

} /* namespace Flix */

#endif /* NETWORKING_PROTOCOL_TELNETSERVERCONNECTION_H_ */
