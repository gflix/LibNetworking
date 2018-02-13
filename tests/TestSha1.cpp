#include <gtest/gtest.h>
#include <networking/digest/Sha1.h>

TEST(Sha1, EmptyMessageHash)
{
    Flix::Sha1 sha1;

    sha1.reset();
    EXPECT_EQ(sha1.getHash(),
        "\xda\x39\xa3\xee\x5e\x6b\x4b\x0d\x32\x55\xbf\xef\x95\x60\x18\x90\xaf\xd8\x07\x09");
}
