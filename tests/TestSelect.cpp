#include <gtest/gtest.h>
#include <networking/Select.h>

TEST(Select, Defaults)
{
    Flix::Select select;

    EXPECT_TRUE(select.getAutoReloadTimeout());
    EXPECT_EQ(select.getTimeout().tv_sec, 15);
    EXPECT_EQ(select.getTimeout().tv_usec, 0);

    EXPECT_EQ(select.getWriteDescriptorCount(), 0);
}

TEST(Select, ReadDescriptors)
{
    Flix::Select select;

    EXPECT_EQ(select.getReadDescriptorCount(), 0);

    EXPECT_ANY_THROW(select.addReadDescriptor(-1));

    EXPECT_NO_THROW(select.addReadDescriptor(0));
    EXPECT_EQ(select.getReadDescriptorCount(), 1);

    EXPECT_NO_THROW(select.removeReadDescriptor(0));
    EXPECT_EQ(select.getReadDescriptorCount(), 0);
}

TEST(Select, WriteDescriptors)
{
    Flix::Select select;

    EXPECT_EQ(select.getWriteDescriptorCount(), 0);

    EXPECT_ANY_THROW(select.addWriteDescriptor(-1));

    EXPECT_NO_THROW(select.addWriteDescriptor(0));
    EXPECT_EQ(select.getWriteDescriptorCount(), 1);

    EXPECT_NO_THROW(select.removeWriteDescriptor(0));
    EXPECT_EQ(select.getWriteDescriptorCount(), 0);
}

TEST(Select, Timeout)
{
    Flix::Select select;

    EXPECT_EQ(select.getTimeout().tv_sec, select.getRemainingTime().tv_sec);
    EXPECT_EQ(select.getTimeout().tv_usec, select.getRemainingTime().tv_usec);

    select.setAutoReloadTimeout(true);
    EXPECT_TRUE(select.getAutoReloadTimeout());

    select.setAutoReloadTimeout(false);
    EXPECT_FALSE(select.getAutoReloadTimeout());
}
