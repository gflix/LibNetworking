#include <networking/protocol/Slip.h>

#define FRAME_DELIMITER (0xc0)

namespace Flix {

Slip::Slip()
{
}

Slip::~Slip()
{
}

void Slip::appendReceivedData(const std::string& receivedData)
{
    receiveBuffer += receivedData;
}

void Slip::resetReceiveBuffer(void)
{
    receiveBuffer.clear();
}

const std::string Slip::getReceiveBuffer(void) const
{
    return
        receiveBuffer;
}

void Slip::getFrameDelimiters(std::string::size_type& first, std::string::size_type& second) const
{
    second = std::string::npos;
    first = receiveBuffer.find(FRAME_DELIMITER);
    if (first == std::string::npos)
    {
        return;
    }

    second = receiveBuffer.find(FRAME_DELIMITER, first + 1);
    if (second == std::string::npos)
    {
        first = std::string::npos;
        return;
    }

    if (second == (first + 1))
    {
        first = second;

        second = receiveBuffer.find(FRAME_DELIMITER, first + 1);
        if (second == std::string::npos)
        {
            first = std::string::npos;
            return;
        }
    }
}

bool Slip::hasFrame(void) const
{
    std::string::size_type firstDelimiter, secondDelimiter;
    getFrameDelimiters(firstDelimiter, secondDelimiter);

    return
        firstDelimiter != std::string::npos &&
        secondDelimiter != std::string::npos;
}

void Slip::getFrame(std::string& frame)
{
    frame.clear();
}

} /* namespace Flix */