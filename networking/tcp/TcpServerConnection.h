#ifndef NETWORKING_TCP_TCPSERVERCONNECTION_H_
#define NETWORKING_TCP_TCPSERVERCONNECTION_H_

#include <string>
#include <networking/tcp/GenericTcpConnection.h>

namespace Flix {

class TcpServerConnection: public GenericTcpConnection {
public:
    TcpServerConnection(int descriptor);
    virtual ~TcpServerConnection();
};

} /* namespace Flix */

#endif /* NETWORKING_TCP_TCPSERVERCONNECTION_H_ */
