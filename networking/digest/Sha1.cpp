#include <cassert>
#include <networking/digest/Sha1.h>

#define INITIAL_VALUE_H0 (0x67452301UL)
#define INITIAL_VALUE_H1 (0xefcdab89UL)
#define INITIAL_VALUE_H2 (0x98badcfeUL)
#define INITIAL_VALUE_H3 (0x10325476UL)
#define INITIAL_VALUE_H4 (0xc3d2e1f0UL)

namespace Flix {

Sha1::Sha1()
{
}

Sha1::~Sha1()
{
}

void Sha1::appendMessage(const std::string& message)
{
    this->message += message;
}

const std::string& Sha1::getMessage(void) const
{
    return message;
}

void Sha1::reset(void)
{
    message.clear();
}

std::string Sha1::getHash(void) const
{
    uint32_t h[5];

    h[0] = INITIAL_VALUE_H0;
    h[1] = INITIAL_VALUE_H1;
    h[2] = INITIAL_VALUE_H2;
    h[3] = INITIAL_VALUE_H3;
    h[4] = INITIAL_VALUE_H4;

    std::string paddedMessage { message };
    uint64_t messageBits = message.size() * 8;

    paddedMessage += '\x80';

    size_t paddedMessageSize = paddedMessage.size();
    size_t remainingBytes = 63 - ((paddedMessageSize + 7) % 64);

    for (; remainingBytes > 0; --remainingBytes)
    {
        paddedMessage += '\x00';
    }
    paddedMessage += (messageBits >> 56) & 0xff;
    paddedMessage += (messageBits >> 48) & 0xff;
    paddedMessage += (messageBits >> 40) & 0xff;
    paddedMessage += (messageBits >> 32) & 0xff;
    paddedMessage += (messageBits >> 24) & 0xff;
    paddedMessage += (messageBits >> 16) & 0xff;
    paddedMessage += (messageBits >> 8) & 0xff;
    paddedMessage += messageBits & 0xff;

    assert((paddedMessage.size() % 64) == 0);

    while (!paddedMessage.empty())
    {
        std::string messageBlock = paddedMessage.substr(0, 64);
        paddedMessage.erase(0, 64);

        uint32_t w[80];
        int byteIndex = 0;
        for (int i = 0; i < 16; ++i)
        {
            w[i] =
                messageBlock[byteIndex] << 24 |
                messageBlock[byteIndex + 1] << 16 |
                messageBlock[byteIndex + 2] << 8 |
                messageBlock[byteIndex + 3];

            byteIndex += 4;
        }
        for (int i = 16; i < 80; ++i)
        {
            w[i] = w[i - 3] ^ w[i - 8] ^ w[i - 14] ^ w[i - 16];
            w[i] = w[i] >> 31 | w[i] << 1;
        }

        uint32_t a[5];
        for (int i = 0; i < 5; ++i)
        {
            a[i] = h[i];
        }

        for (int i = 0; i < 80; i++)
        {
            uint32_t f = 0;
            uint32_t k = 0;

            if (i < 20)
            {
                f = (a[1] & a[2]) | (~a[1] & a[3]);
                k = 0x5a827999;
            }
            else if (i < 40)
            {
                f = a[1] ^ a[2] ^ a[3];
                k = 0x6ed9eba1;
            }
            else if (i < 60)
            {
                f = (a[1] & a[2]) | (a[1] & a[3]) | (a[2] & a[3]);
                k = 0x8f1bbcdc;
            }
            else
            {
                f = a[1] ^ a[2] ^ a[3];
                k = 0xca62c1d6;
            }

            uint32_t temp = (a[0] >> 27 | a[0] << 5) + f + a[4] + k + w[i];
            a[4] = a[3];
            a[3] = a[2];
            a[2] = a[1] >> 2 | a[1] << 30;
            a[1] = a[0];
            a[0] = temp;
        }

        for (int i = 0; i < 5; ++i)
        {
            h[i] += a[i];
        }
    }

    std::string hash;
    for (int i = 0; i < 5; ++i)
    {
        hash += (h[i] >> 24) & 0xff;
        hash += (h[i] >> 16) & 0xff;
        hash += (h[i] >> 8) & 0xff;
        hash += h[i] & 0xff;
    }

    assert(hash.size() == 20);

    return hash;
}

} /* namespace Flix */
