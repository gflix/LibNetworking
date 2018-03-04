#include <gtest/gtest.h>
#include <networking/tcp/TcpServer.h>

TEST(TcpServer, StartValueRanges)
{
    Flix::TcpServer tcpServer;

    int invalidTcpPortLow = 0;
    int invalidTcpPortHigh = 65536;
    Flix::Protocol dummyProtocol = Flix::Protocol::IPV4;
    int dummyTcpPort = 6635;
    Flix::Protocol invalidProtocol = static_cast<Flix::Protocol>(-1);

    EXPECT_ANY_THROW(tcpServer.start(invalidTcpPortLow, dummyProtocol));
    EXPECT_ANY_THROW(tcpServer.start(invalidTcpPortHigh, dummyProtocol));
    EXPECT_ANY_THROW(tcpServer.start(dummyTcpPort, invalidProtocol));
}

TEST(TcpServer, Defaults)
{
    Flix::TcpServer tcpServer;

    EXPECT_FALSE(tcpServer.isConnected());
    EXPECT_ANY_THROW(tcpServer.getDescriptor());
}
