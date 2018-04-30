#include <stdexcept>
#include <networking/protocol/Slip.h>

#define FRAME_DELIMITER (0xc0)
#define FRAME_ESCAPE_CHARACTER (0xdb)
#define FRAME_REPLACEMENT_DELIMITER (0xdc)
#define FRAME_REPLACEMENT_ESCAPE_CHARACTER (0xdd)

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

void Slip::getFrame(SlipFrame& frame)
{
    frame.clear();

    if (!hasFrame())
    {
        throw std::runtime_error("no frame in receive buffer");
    }

    std::string::size_type firstDelimiter, secondDelimiter;
    getFrameDelimiters(firstDelimiter, secondDelimiter);

    frame = unescapeFrame(receiveBuffer.substr(firstDelimiter + 1, secondDelimiter - firstDelimiter - 1));
    receiveBuffer.erase(0, secondDelimiter + 1);
}

void Slip::getFrames(SlipFrames& frames)
{
    frames.clear();
    while (hasFrame())
    {
        SlipFrame frame;
        getFrame(frame);
        frames.push_back(frame);
    }
}

std::string Slip::encodeFrame(const SlipFrame& frame)
{
    std::string frameDelimiter;
    frameDelimiter.push_back(FRAME_DELIMITER);
    return
        frameDelimiter + escapeFrame(frame) + frameDelimiter;
}

std::string Slip::escapeFrame(const SlipFrame& input)
{
    std::string output;

    for (auto& character: input)
    {
        if (static_cast<unsigned char>(character) == FRAME_DELIMITER)
        {
            output += FRAME_ESCAPE_CHARACTER;
            output += FRAME_REPLACEMENT_DELIMITER;
        }
        else if (static_cast<unsigned char>(character) == FRAME_ESCAPE_CHARACTER)
        {
            output += FRAME_ESCAPE_CHARACTER;
            output += FRAME_REPLACEMENT_ESCAPE_CHARACTER;
        }
        else
        {
            output += character;
        }
    }

    return output;
}

std::string Slip::unescapeFrame(const SlipFrame& input)
{
    std::string output;

    for (auto character = input.cbegin(); character != input.cend(); ++character)
    {
        if (static_cast<unsigned char>(*character) == FRAME_DELIMITER)
        {
            throw std::out_of_range("delimiter character not allowed in frame");
        }
        if (static_cast<unsigned char>(*character) != FRAME_ESCAPE_CHARACTER)
        {
            output += *character;
        }
        else
        {
            ++character;
            if (character == input.cend())
            {
                throw std::runtime_error("unexpected end of input");
            }
            switch (static_cast<unsigned char>(*character))
            {
            case FRAME_REPLACEMENT_DELIMITER:
                output += FRAME_DELIMITER;
                break;
            case FRAME_REPLACEMENT_ESCAPE_CHARACTER:
                output += FRAME_ESCAPE_CHARACTER;
                break;
            default:
                throw std::out_of_range("escaped character is unknown");
            }
        }
    }

    return output;
}

} /* namespace Flix */
