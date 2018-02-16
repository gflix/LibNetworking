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

std::string Conversion::hexToBin(const std::string& hex)
{
    if (hex.size() % 2)
    {
        throw std::invalid_argument("invalid character count in input");
    }

    std::string bin;

    auto iterator = hex.cbegin();

    while (iterator != hex.cend())
    {
        unsigned char byte;

        byte = decodeHexDigit(*iterator) << 4;
        ++iterator;
        byte |= decodeHexDigit(*iterator);
        ++iterator;

        bin += byte;
    }

    return bin;
}

unsigned char Conversion::decodeHexDigit(const char& digit)
{
    if (digit >= '0' && digit <= '9')
    {
        return digit - '0';
    }
    else if (digit >= 'A' && digit <= 'F')
    {
        return digit - 'A' + 10;
    }
    else if (digit >= 'a' && digit <= 'f')
    {
        return digit - 'a' + 10;
    }
    throw std::invalid_argument("invalid hex digit");
}

} /* namespace Flix */
