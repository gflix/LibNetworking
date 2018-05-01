#include <networking/utils/LogLevel.h>

namespace Flix {

LogLevel identifierToLogLevel(const std::string& identifier)
{
    if (identifier == "ERROR") {
        return LogLevel::ERROR;
    } else if (identifier == "WARNING") {
        return LogLevel::WARNING;
    } else if (identifier == "NOTICE") {
        return LogLevel::NOTICE;
    } else if (identifier == "INFO") {
        return LogLevel::INFO;
    }
    return LogLevel::DEBUG;
}

std::string logLevelToIdentifier(LogLevel logLevel)
{
    switch (logLevel) {
    case LogLevel::ERROR:
        return "ERROR";
    case LogLevel::WARNING:
        return "WARNING";
    case LogLevel::NOTICE:
        return "NOTICE";
    case LogLevel::INFO:
        return "INFO";
    default:
        break;
    }
    return "DEBUG";
}

} /* namespace Flix */
