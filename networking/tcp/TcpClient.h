#ifndef TCPCLIENT_TCPCLIENT_H_
#define TCPCLIENT_TCPCLIENT_H_

#include <string>

namespace Flix {

class TcpClient {
public:
    TcpClient();
    virtual ~TcpClient();

    void connect(std::string host, int port);
    void disconnect(void);

    bool isConnected(void) const;
    int getDescriptor(void) const;

    void send(const std::string& data) const;
    void receive(std::string& data, size_t bufferSize) const;

protected:
    bool withinRange(int value, int min, int max) const;

private:
    int descriptor;
};

} /* namespace Flix */

#endif /* TCPCLIENT_TCPCLIENT_H_ */
