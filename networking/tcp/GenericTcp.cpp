#include <stdexcept>
#include <networking/tcp/GenericTcp.h>

namespace Flix {

GenericTcp::GenericTcp():
    descriptor(TCP_INVALID_DESCRIPTOR)
{
}

GenericTcp::~GenericTcp()
{
}

bool GenericTcp::isConnected(void) const
{
    return
        descriptor > TCP_INVALID_DESCRIPTOR;
}

int GenericTcp::getDescriptor(void) const
{
    if (!isConnected())
    {
        throw std::runtime_error("not connected");
    }

    return
        descriptor;
}

bool GenericTcp::withinRange(int value, int min, int max) const
{
    return
        value >= min &&
        value <= max;
}

} /* namespace Flix */
