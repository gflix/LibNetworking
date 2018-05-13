#include <gtest/gtest.h>
#include <networking/Networking.h>

TEST(Networking, PackageInfo)
{
    EXPECT_EQ(Flix::Networking::getPackageInfo(), "libnetworking 0.2.4");
}
