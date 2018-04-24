#include <gtest/gtest.h>
#include <networking/protocol/Slip.h>

TEST(Protocol, SlipReceiveBuffer)
{
    Flix::Slip slip;
    std::string inputA { "1234" };
    std::string inputB { "5678" };

    EXPECT_TRUE(slip.getReceiveBuffer().empty());
    slip.appendReceivedData(inputA);
    EXPECT_EQ(slip.getReceiveBuffer(), inputA);
    slip.appendReceivedData(inputB);
    EXPECT_EQ(slip.getReceiveBuffer(), inputA + inputB);
    slip.resetReceiveBuffer();
    EXPECT_TRUE(slip.getReceiveBuffer().empty());
}

TEST(Protocol, SlipFrameDelimiters)
{
    Flix::Slip slip;
    std::string::size_type firstDelimiter;
    std::string::size_type secondDelimiter;

    slip.getFrameDelimiters(firstDelimiter, secondDelimiter);
    EXPECT_EQ(firstDelimiter, std::string::npos);
    EXPECT_EQ(secondDelimiter, std::string::npos);
    EXPECT_FALSE(slip.hasFrame());

    slip.appendReceivedData("invalid\xC0""frame\xC0""invalid");
    EXPECT_EQ(slip.getReceiveBuffer().size(), 21);
    slip.getFrameDelimiters(firstDelimiter, secondDelimiter);
    EXPECT_EQ(firstDelimiter, 7);
    EXPECT_EQ(secondDelimiter, 13);
    EXPECT_TRUE(slip.hasFrame());

    slip.resetReceiveBuffer();
    slip.appendReceivedData("invalid\xC0\xC0""invalid");
    EXPECT_EQ(slip.getReceiveBuffer().size(), 16);
    slip.getFrameDelimiters(firstDelimiter, secondDelimiter);
    EXPECT_EQ(firstDelimiter, std::string::npos);
    EXPECT_EQ(secondDelimiter, std::string::npos);
    EXPECT_FALSE(slip.hasFrame());

    slip.resetReceiveBuffer();
    slip.appendReceivedData("invalid\xC0\xC0""frame\xC0""invalid");
    EXPECT_EQ(slip.getReceiveBuffer().size(), 22);
    slip.getFrameDelimiters(firstDelimiter, secondDelimiter);
    EXPECT_EQ(firstDelimiter, 8);
    EXPECT_EQ(secondDelimiter, 14);
    EXPECT_TRUE(slip.hasFrame());
}
