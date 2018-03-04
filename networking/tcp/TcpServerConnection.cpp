#include <networking/tcp/TcpServerConnection.h>

namespace Flix {

TcpServerConnection::TcpServerConnection(int descriptor):
    GenericTcpConnection()
{
    this->descriptor = descriptor;
}

TcpServerConnection::~TcpServerConnection()
{
}

} /* namespace Flix */
