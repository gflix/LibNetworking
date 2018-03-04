#ifndef TCPCLIENT_TCPCLIENT_H_
#define TCPCLIENT_TCPCLIENT_H_

#include <string>
#include <networking/tcp/GenericTcp.h>

namespace Flix {

class TcpClient: public GenericTcp {
public:
    TcpClient();
    virtual ~TcpClient();

    void connect(std::string host, int port);
    void disconnect(void);

    void send(const std::string& data) const;
    void receive(std::string& data, size_t bufferSize) const;
};

} /* namespace Flix */

#endif /* TCPCLIENT_TCPCLIENT_H_ */
