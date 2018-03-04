#include <unistd.h>
#include <iostream>
#include <string>
#include <networking/tcp/TcpServer.h>

using namespace std;

void printUsage(const string& programName)
{
    cerr << "USAGE: " << programName << " PROTOCOL PORT" << endl;
    cerr << endl;
    cerr << "Arguments:" << endl;
    cerr << "  PROTOCL  4 = IPv4, 6 = IPv6" << endl;
    cerr << "  PORT     server TCP port" << endl;
    cerr << endl;
}

int main(int argc, char* argv[])
{
    string programName { argv[0] };
    if (argc < 3)
    {
        printUsage(programName);
        return 1;

    }

    int protocolVersion = std::stol(argv[1]);
    int port = std::stol(argv[2]);

    Flix::Protocol protocol = Flix::Protocol::UNDEFINED;
    switch (protocolVersion)
    {
    case 4:
        protocol = Flix::Protocol::IPV4;
        break;
    case 6:
        protocol = Flix::Protocol::IPV6;
        break;
    default:
        break;
    }

    Flix::TcpServer tcpServer;
    tcpServer.start(port, protocol);

    while (1)
    {
        sleep(10);
    }

    return 0;
}
