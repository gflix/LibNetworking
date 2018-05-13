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

TEST(Conversion, BinToAscii)
{
    std::string bin { "\x01 234 \x05" };
    std::string expected { ". 234 ." };

    EXPECT_EQ(Flix::Conversion::binToAscii(bin), expected);
}

TEST(Conversion, Reverse)
{
    std::string input { "0123456789" };
    std::string expected { "9876543210" };

    EXPECT_EQ(Flix::Conversion::reverse(input), expected);
}

TEST(Conversion, BinToUnsigned)
{
    std::string inputA { "\xab" };
    unsigned long long expectedA = 171;
    std::string inputB { "\xab\xcd" };
    unsigned long long expectedB = 52651;
    std::string inputC { "\xab\xcd\xef" };
    unsigned long long expectedC = 15715755;
    std::string inputD { "\xab\xcd\xef\x01" };
    unsigned long long expectedD = 32492971;
    std::string inputE { "\xab\xcd\xef\x01\x23" };
    unsigned long long expectedE = 150356348331;
    std::string inputF { "\xab\xcd\xef\x01\x23\x45" };
    unsigned long long expectedF = 76016658664875;
    std::string inputG { "\xab\xcd\xef\x01\x23\x45\x67" };
    unsigned long long expectedG = 29067939259862443;
    std::string inputH { "\xab\xcd\xef\x01\x23\x45\x67\x89" };
    unsigned long long expectedH = 9900958322455989675ULL;

    EXPECT_EQ(Flix::Conversion::binToUnsigned(inputA), expectedA);
    EXPECT_EQ(Flix::Conversion::binToUnsigned(inputB), expectedB);
    EXPECT_EQ(Flix::Conversion::binToUnsigned(inputC), expectedC);
    EXPECT_EQ(Flix::Conversion::binToUnsigned(inputD), expectedD);
    EXPECT_EQ(Flix::Conversion::binToUnsigned(inputE), expectedE);
    EXPECT_EQ(Flix::Conversion::binToUnsigned(inputF), expectedF);
    EXPECT_EQ(Flix::Conversion::binToUnsigned(inputG), expectedG);
    EXPECT_EQ(Flix::Conversion::binToUnsigned(inputH), expectedH);
}

TEST(Conversion, BinToUnsignedFromCharacter)
{
    char inputA = '\xab';
    unsigned long long expectedA = 171;

    EXPECT_EQ(Flix::Conversion::binToUnsigned(inputA), expectedA);
}

TEST(Conversion, BinToUnsignedInvalidArgument)
{
    std::string input { "123456789" };

    EXPECT_ANY_THROW(Flix::Conversion::binToUnsigned(input));
}

TEST(Conversion, BinToSigned)
{
    std::string inputA { "\xfd" };
    signed long long expectedA = -3;
    std::string inputB { "\x7f" };
    signed long long expectedB = 127;
    std::string inputC { "\xfe\xff\xff\xff\xff\xff\xff\xff" };
    signed long long expectedC = -2;

    EXPECT_EQ(Flix::Conversion::binToSigned(inputA), expectedA);
    EXPECT_EQ(Flix::Conversion::binToSigned(inputB), expectedB);
    EXPECT_EQ(Flix::Conversion::binToSigned(inputC), expectedC);
}

TEST(Conversion, BinToSignedFromCharacter)
{
    char inputA = '\xfe';
    signed long long expectedA = -2;

    EXPECT_EQ(Flix::Conversion::binToSigned(inputA), expectedA);
}
