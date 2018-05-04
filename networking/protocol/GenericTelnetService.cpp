#include <networking/utils/Log.h>
#include <networking/protocol/TelnetServerConnection.h>
#include <networking/protocol/GenericTelnetService.h>

namespace Flix {

GenericTelnetService::GenericTelnetService()
{
}

GenericTelnetService::~GenericTelnetService()
{
}

void GenericTelnetService::processLine(const std::string& line, TelnetServerConnection& connection)
{
    if (line == "quit")
    {
        connection.closeConnection();
    }

    connection.send("unknown command \"" + line + "\" (" + std::to_string(line.size()) + ")\n");
}

} /* namespace Flix */
