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

TEST(Protocol, SlipGetFrame)
{
    Flix::Slip slip;
    std::string frame;

    EXPECT_ANY_THROW(slip.getFrame(frame));

    slip.appendReceivedData("invalid\xC0""frame\xC0""INVALID");
    EXPECT_NO_THROW(slip.getFrame(frame));
    EXPECT_EQ(frame, "frame");
    EXPECT_EQ(slip.getReceiveBuffer(), "INVALID");
}

TEST(Protocol, SlipGetFrames)
{
    Flix::Slip slip;
    Flix::SlipFrames frames;

    slip.appendReceivedData("invalid\xC0""frame\xC0\xC0""FRAME\xC0""INVALID");
    EXPECT_NO_THROW(slip.getFrames(frames));
    EXPECT_EQ(frames.size(), 2);
    EXPECT_EQ(frames[0], "frame");
    EXPECT_EQ(frames[1], "FRAME");
    EXPECT_EQ(slip.getReceiveBuffer(), "INVALID");
}

TEST(Protocol, SlipEscapeFrame)
{
    std::string inputA { "1234" };
    std::string inputB { "1234\xC0""5678" };
    std::string expectB { "1234\xDB\xDC""5678" };
    std::string inputC { "12\xC0""34\xDB""56" };
    std::string expectC { "12\xDB\xDC""34\xDB\xDD""56" };
    std::string inputD { "1234\xC0\xC0""5678" };
    std::string expectD { "1234\xDB\xDC\xDB\xDC""5678" };

    EXPECT_EQ(Flix::Slip::escapeFrame(inputA), inputA);
    EXPECT_EQ(Flix::Slip::escapeFrame(inputB), expectB);
    EXPECT_EQ(Flix::Slip::escapeFrame(inputC), expectC);
    EXPECT_EQ(Flix::Slip::escapeFrame(inputD), expectD);
}

TEST(Protocol, SlipUnescapeFrame)
{
    std::string inputA { "1234" };
    std::string inputB { "12\xC0""34" };
    std::string inputC { "1234\xDB\xDC""5678" };
    std::string expectC { "1234\xC0""5678" };
    std::string inputD { "12\xDB\xDC""34\xDB\xDD""56" };
    std::string expectD { "12\xC0""34\xDB""56" };
    std::string inputE { "1234\xDB\xDC\xDB\xDC""5678" };
    std::string expectE { "1234\xC0\xC0""5678" };

    EXPECT_EQ(Flix::Slip::unescapeFrame(inputA), inputA);
    EXPECT_ANY_THROW(Flix::Slip::unescapeFrame(inputB));
    EXPECT_EQ(Flix::Slip::unescapeFrame(inputC), expectC);
    EXPECT_EQ(Flix::Slip::unescapeFrame(inputD), expectD);
    EXPECT_EQ(Flix::Slip::unescapeFrame(inputE), expectE);
}

TEST(Protocol, SlipEncodeFrame)
{
    std::string inputA { "1234" };
    std::string expectA { "\xC0""1234\xC0" };
    std::string inputB { "12\xC0""34" };
    std::string expectB { "\xC0""12\xDB\xDC""34\xC0" };

    EXPECT_EQ(Flix::Slip::encodeFrame(inputA), expectA);
    EXPECT_EQ(Flix::Slip::encodeFrame(inputB), expectB);
}
