#ifndef NETWORKING_TCP_TCPSERVER_H_
#define NETWORKING_TCP_TCPSERVER_H_

#include <networking/Protocol.h>
#include <networking/tcp/GenericTcp.h>

namespace Flix {

class TcpServer: public GenericTcp {
public:
    TcpServer();
    virtual ~TcpServer();

    void start(int port, Protocol protocol = Protocol::IPV4);
    void stop(void);
};

} /* namespace Flix */

#endif /* NETWORKING_TCP_TCPSERVER_H_ */
