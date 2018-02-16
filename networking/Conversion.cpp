#include <stdexcept>
#include <networking/Conversion.h>

namespace Flix {

const char hexDigits[2][16] = {
    { '0', '1', '2', '3', '4', '5', '6', '7',
      '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'},
    { '0', '1', '2', '3', '4', '5', '6', '7',
      '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'},
};

std::string Conversion::binToHex(const std::string& bin, HexDigitCase hexDigitCase)
{
    std::string hex;

    int hexDigitSet;
    switch (hexDigitCase)
    {
    case HexDigitCase::LOWER:
        hexDigitSet = 0;
        break;
    case HexDigitCase::UPPER:
        hexDigitSet = 1;
        break;
    default:
        throw std::invalid_argument("invalid argument for hexDigitCase");
    }

    for (auto& element: bin)
    {
        hex += hexDigits[hexDigitSet][(element >> 4) & 0x0f];
        hex += hexDigits[hexDigitSet][element & 0x0f];
    }

    return hex;
}

} /* namespace Flix */
