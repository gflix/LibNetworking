#ifndef NETWORKING_TCP_GENERICTCPCONNECTION_H_
#define NETWORKING_TCP_GENERICTCPCONNECTION_H_

#include <string>
#include <networking/tcp/GenericTcp.h>

#define TCP_RECEIVE_BUFFER_SIZE_DEFAULT (1024)

namespace Flix {

class GenericTcpConnection: public GenericTcp {
public:
    GenericTcpConnection();
    virtual ~GenericTcpConnection();

    void disconnect(void);

    void send(const std::string& data) const;
    void receive(std::string& data, size_t bufferSize = TCP_RECEIVE_BUFFER_SIZE_DEFAULT) const;
};

} /* namespace Flix */

#endif /* NETWORKING_TCP_GENERICTCPCONNECTION_H_ */
