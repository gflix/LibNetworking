#include <gtest/gtest.h>
#include <networking/Conversion.h>

TEST(Conversion, BinToHex)
{
    std::string bin { "\x01\x23\x45\x67\x89\xab\xcd\xef" };
    std::string expectedLower { "0123456789abcdef" };
    std::string expectedUpper { "0123456789ABCDEF" };

    EXPECT_EQ(Flix::Conversion::binToHex(bin),
        expectedLower);
    EXPECT_EQ(Flix::Conversion::binToHex(bin, Flix::HexDigitCase::LOWER),
        expectedLower);
    EXPECT_EQ(Flix::Conversion::binToHex(bin, Flix::HexDigitCase::UPPER),
        expectedUpper);
}
