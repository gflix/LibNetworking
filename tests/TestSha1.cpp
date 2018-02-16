#include <gtest/gtest.h>
#include <networking/Conversion.h>
#include <networking/digest/Sha1.h>

TEST(Sha1, EmptyMessageHash)
{
    Flix::Sha1 sha1;

    std::string expected { "da39a3ee5e6b4b0d3255bfef95601890afd80709" };

    sha1.reset();
    EXPECT_EQ(Flix::Conversion::binToHex(sha1.getHash()), expected);
}

TEST(Sha1, TestMessageHash)
{
    Flix::Sha1 sha1;

    std::string messageA { "test" };
    std::string expectedA { "a94a8fe5ccb19ba61c4c0873d391e987982fbbd3" };
    std::string messageB { "1234" };
    std::string expectedB { "9bc34549d565d9505b287de0cd20ac77be1d3f2c" };
    std::string expectedC { "test1234" };

    sha1.reset();
    sha1.appendMessage(messageA);
    EXPECT_EQ(Flix::Conversion::binToHex(sha1.getHash()), expectedA);
    sha1.appendMessage(messageB);
    EXPECT_EQ(Flix::Conversion::binToHex(sha1.getHash()), expectedB);
    EXPECT_EQ(sha1.getMessage(), expectedC);
}
