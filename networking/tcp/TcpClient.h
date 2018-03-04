#ifndef TCPCLIENT_TCPCLIENT_H_
#define TCPCLIENT_TCPCLIENT_H_

#include <string>
#include <networking/tcp/GenericTcpConnection.h>

namespace Flix {

class TcpClient: public GenericTcpConnection {
public:
    TcpClient();
    virtual ~TcpClient();

    void connect(std::string host, int port);
};

} /* namespace Flix */

#endif /* TCPCLIENT_TCPCLIENT_H_ */
