#ifndef NETWORKING_UTILS_LOGLEVEL_H_
#define NETWORKING_UTILS_LOGLEVEL_H_

#include <string>

namespace Flix {

enum class LogLevel {
    ERROR = 0,
    WARNING = 1,
    NOTICE = 2,
    INFO = 3,
    DEBUG = 4
};

LogLevel identifierToLogLevel(const std::string& identifier);
std::string logLevelToIdentifier(LogLevel state);

} /* namespace Flix */

#endif /* NETWORKING_UTILS_LOGLEVEL_H_ */
