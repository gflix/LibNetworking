#ifndef NETWORKING_CONVERSION_H_
#define NETWORKING_CONVERSION_H_

#include <string>

namespace Flix {

enum class HexDigitCase {
    LOWER,
    UPPER,
};

class Conversion {
public:
    static std::string binToHex(
        const std::string& bin,
        HexDigitCase hexDigitCase = HexDigitCase::LOWER);
    static std::string hexToBin(const std::string& hex);

private:
    static unsigned char decodeHexDigit(const char& digit);
};

} /* namespace Flix */

#endif /* NETWORKING_CONVERSION_H_ */
