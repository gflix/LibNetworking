#include <networking/Autoconf.h>
#include <networking/Networking.h>

#ifndef PACKAGE_STRING
#define PACKAGE_STRING "unknown"
#endif

namespace Flix {

std::string Networking::getPackageInfo(void)
{
    return { PACKAGE_STRING };
}

} /* namespace Flix */
