#include <stdexcept>
#include <networking/serial/Baudrate.h>

namespace Flix {

Baudrate identifierToBaudrate(std::string& identifier)
{
    return intToBaudrate(std::stoi(identifier));
}

Baudrate intToBaudrate(int baudrate)
{
    switch (baudrate)
    {
    case 38400:
        return Baudrate::RATE_38400;
    default:
        throw std::invalid_argument("invalid baudrate \"" + std::to_string(baudrate) + "\"");
    }
}

int baudrateToInt(Baudrate baudrate)
{
    switch (baudrate)
    {
    case Baudrate::RATE_38400:
        return 38400;
    default:
        throw std::invalid_argument("invalid baudrate");
    }
}

} /* namespace Flix */
