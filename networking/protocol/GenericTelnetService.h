#ifndef NETWORKING_PROTOCOL_GENERICTELNETSERVICE_H_
#define NETWORKING_PROTOCOL_GENERICTELNETSERVICE_H_

#include <string>

namespace Flix {

class TelnetServerConnection;

class GenericTelnetService {
public:
    GenericTelnetService();
    virtual ~GenericTelnetService();

    virtual void processLine(const std::string& line, TelnetServerConnection& connection);
};

} /* namespace Flix */

#endif /* NETWORKING_PROTOCOL_GENERICTELNETSERVICE_H_ */
