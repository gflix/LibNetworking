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

TEST(Conversion, BinToHexInvalidArgument)
{
    EXPECT_ANY_THROW(Flix::Conversion::binToHex(std::string(),
        static_cast<Flix::HexDigitCase>(-1)));
}

TEST(Conversion, HexToBin)
{
    std::string hexLower { "0123456789abcdef" };
    std::string hexUpper { "0123456789ABCDEF" };
    std::string hexMixed { "0123456789aBcDeF" };
    std::string expected { "\x01\x23\x45\x67\x89\xab\xcd\xef" };

    EXPECT_EQ(Flix::Conversion::hexToBin(hexLower), expected);
    EXPECT_EQ(Flix::Conversion::hexToBin(hexUpper), expected);
    EXPECT_EQ(Flix::Conversion::hexToBin(hexMixed), expected);
}

TEST(Conversion, HexToBinInvalidArgument)
{
    EXPECT_ANY_THROW(Flix::Conversion::hexToBin("123"));
    EXPECT_ANY_THROW(Flix::Conversion::hexToBin("01234z"));
}

TEST(Conversion, HexToBinToHex)
{
    std::string hex { "0123456789abcdef" };

    EXPECT_EQ(Flix::Conversion::binToHex(Flix::Conversion::hexToBin(hex)),
        hex);
}
