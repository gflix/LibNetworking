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

std::string Conversion::binToHexEscaped(const std::string& bin)
{
    std::string hex;

    for (auto& element: bin)
    {
        hex += "\\x";
        hex += hexDigits[0][(element >> 4) & 0x0f];
        hex += hexDigits[0][element & 0x0f];
    }

    return hex;
}

std::string Conversion::binToAscii(const std::string& bin)
{
    std::string ascii;

    for (auto& element: bin)
    {
        int value = static_cast<unsigned char>(element);
        if (value >= 32 && value < 127)
        {
            ascii += element;
        }
        else
        {
            ascii += '.';
        }
    }

    return ascii;
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

std::string Conversion::reverse(const std::string& text)
{
    std::string reversedText;

    for (auto it = text.crbegin(); it != text.crend(); ++it)
    {
        reversedText += *it;
    }

    return reversedText;
}

unsigned long long Conversion::binToUnsigned(const std::string& bin)
{
    if (bin.size() > 8)
    {
        throw std::invalid_argument("too much input");
    }

    unsigned long long value = 0;
    for (auto it = bin.crbegin(); it != bin.crend(); ++it)
    {
        unsigned char characterValue = static_cast<unsigned char>(*it);

        value = (value << 8) | characterValue;
    }

    return value;
}

unsigned long long Conversion::binToUnsigned(char character)
{
    return binToUnsigned(std::string(1, character));
}

signed long long Conversion::binToSigned(const std::string& bin)
{
    std::string paddedBin { bin };

    if (!paddedBin.empty())
    {
        // if the most significant bit is set, pad the input with 0xff until its 8 bytes long
        if (static_cast<unsigned char>(paddedBin[paddedBin.size() - 1]) & 0x80)
        {
            while (paddedBin.size() < 8)
            {
                paddedBin += '\xff';
            }
        }
    }

    return static_cast<signed long long>(binToUnsigned(paddedBin));
}

signed long long Conversion::binToSigned(char character)
{
    return binToSigned(std::string(1, character));
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
