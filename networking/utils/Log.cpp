#include <stdio.h>
#include <unistd.h>
#include <ctime>
#include <iostream>
#include <Log.h>

#ifdef HAVE_CONFIG_H
#include <networking/Autoconf.h>
#endif

#ifdef HAVE_SYSTEMD_SD_DAEMON_H
#include <systemd/sd-daemon.h>
#endif

namespace Flix {

Log Log::instance = {};

Log::Log():
    Log(LogLevel::DEBUG)
{
}

Log::Log(LogLevel logLevel):
    toTty(true),
    logLevel(logLevel)
{
    determineOutputMode();
}

Log::~Log()
{
}

void Log::error(std::string logMessage) const
{
    if (LogLevel::ERROR <= logLevel) {
#ifdef HAVE_SYSTEMD_SD_DAEMON_H
        if (toTty) {
#endif
            std::cerr << "\033[31;1m" << getTimestamp() << " [E] " << logMessage << "\033[0m" << std::endl;
#ifdef HAVE_SYSTEMD_SD_DAEMON_H
        } else {
            std::cerr << SD_ERR << logMessage << std::endl;
        }
#endif
    }
}

void Log::warning(std::string logMessage) const
{
    if (LogLevel::WARNING <= logLevel) {
#ifdef HAVE_SYSTEMD_SD_DAEMON_H
        if (toTty) {
#endif
            std::cerr << "\033[33;1m" << getTimestamp() << " [W] " << logMessage << "\033[0m" << std::endl;
#ifdef HAVE_SYSTEMD_SD_DAEMON_H
        } else {
            std::cerr << SD_WARNING << logMessage << std::endl;
        }
#endif
    }
}

void Log::notice(std::string logMessage) const
{
    if (LogLevel::NOTICE <= logLevel) {
#ifdef HAVE_SYSTEMD_SD_DAEMON_H
        if (toTty) {
#endif
            std::cout << "\033[1m" << getTimestamp() << " [N] " << logMessage << "\033[0m" << std::endl;
#ifdef HAVE_SYSTEMD_SD_DAEMON_H
        } else {
            std::cerr << SD_NOTICE << logMessage << std::endl;
        }
#endif
    }
}

void Log::info(std::string logMessage) const
{
    if (LogLevel::INFO <= logLevel) {
#ifdef HAVE_SYSTEMD_SD_DAEMON_H
        if (toTty) {
#endif
            std::cout << getTimestamp() << " [I] " << logMessage << std::endl;
#ifdef HAVE_SYSTEMD_SD_DAEMON_H
        } else {
            std::cerr << SD_INFO << logMessage << std::endl;
        }
#endif
    }
}

void Log::debug(std::string logMessage) const
{
    if (LogLevel::DEBUG <= logLevel) {
#ifdef HAVE_SYSTEMD_SD_DAEMON_H
        if (toTty) {
#endif
            std::cout << "\033[30;1m" << getTimestamp() << " [D] " << logMessage << "\033[0m" << std::endl;
#ifdef HAVE_SYSTEMD_SD_DAEMON_H
        } else {
            std::cerr << SD_DEBUG << logMessage << std::endl;
        }
#endif
    }
}

void Log::setLogLevel(LogLevel logLevel)
{
    this->logLevel = logLevel;
}

std::string Log::getTimestamp(void) const
{
    char buffer[128];
    time_t currentTimestamp = time(nullptr);
    strftime(buffer, sizeof(buffer), "%Y-%m-%d %H:%M:%S", localtime(&currentTimestamp));

    return buffer;
}

void Log::determineOutputMode(void)
{
    toTty = isatty(fileno(stdout)) && isatty(fileno(stderr));
}

} /* namespace Flix */
