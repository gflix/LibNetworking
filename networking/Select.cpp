#include <networking/Select.h>

#define AUTO_RELOAD_TIMEOUT_DEFAULT (true)
#define INVALID_DESCRIPTOR (-1)
#define TIMEOUT_SECONDS_DEFAULT (15)

namespace Flix {

Select::Select():
    autoReloadTimeout(AUTO_RELOAD_TIMEOUT_DEFAULT)
{
    FD_ZERO(&selectReadDescriptors);
    FD_ZERO(&selectWriteDescriptors);

    defaultTimeout.tv_sec = TIMEOUT_SECONDS_DEFAULT;
    defaultTimeout.tv_usec = 0;
    reloadTimeout();
}

Select::~Select()
{
}

int Select::execute(void)
{
    int maxDescriptor = 0;

    FD_ZERO(&selectReadDescriptors);
    FD_ZERO(&selectWriteDescriptors);

    for (auto descriptor: readDescriptors)
    {
        FD_SET(descriptor, &selectReadDescriptors);
        maxDescriptor = max(maxDescriptor, descriptor);
    }

    for (auto descriptor: writeDescriptors)
    {
        FD_SET(descriptor, &selectWriteDescriptors);
        maxDescriptor = max(maxDescriptor, descriptor);
    }

    if (autoReloadTimeout)
    {
        reloadTimeout();
    }

    return
        ::select(maxDescriptor + 1, &selectReadDescriptors, &selectWriteDescriptors, nullptr, &timeout);
}

void Select::addReadDescriptor(int descriptor)
{
    addDescriptor(readDescriptors, descriptor);
}

void Select::removeReadDescriptor(int descriptor)
{
    removeDescriptor(readDescriptors, descriptor);
}

void Select::addWriteDescriptor(int descriptor)
{
    addDescriptor(writeDescriptors, descriptor);
}

void Select::removeWriteDescriptor(int descriptor)
{
    removeDescriptor(writeDescriptors, descriptor);
}

size_t Select::getReadDescriptorCount(void) const
{
    return readDescriptors.size();
}

size_t Select::getWriteDescriptorCount(void) const
{
    return writeDescriptors.size();
}

bool Select::readDescriptorIsSet(int descriptor) const
{
    return
        FD_ISSET(descriptor, &selectReadDescriptors);
}

bool Select::writeDescriptorIsSet(int descriptor) const
{
    return
        FD_ISSET(descriptor, &selectWriteDescriptors);
}

void Select::setTimeout(timeval& timeout)
{
    defaultTimeout = timeout;
}

void Select::setTimeout(time_t timeoutSeconds)
{
    timeval timeout;
    timeout.tv_sec = timeoutSeconds;
    timeout.tv_usec = 0;

    setTimeout(timeout);
}

void Select::setTimeout(time_t timeoutSeconds, useconds_t timeoutMicroseconds)
{
    timeval timeout;
    timeout.tv_sec = timeoutSeconds;
    timeout.tv_usec = timeoutMicroseconds;

    setTimeout(timeout);
}

const timeval& Select::getTimeout(void) const
{
    return
        defaultTimeout;
}

const timeval& Select::getRemainingTime(void) const
{
    return
        timeout;
}

void Select::setAutoReloadTimeout(bool enable)
{
    autoReloadTimeout = enable;
}

bool Select::getAutoReloadTimeout(void) const
{
    return
        autoReloadTimeout;
}

void Select::reloadTimeout(void)
{
    timeout = defaultTimeout;
}

void Select::addDescriptor(Descriptors& descriptors, int descriptor)
{
    if (descriptor <= INVALID_DESCRIPTOR)
    {
        throw std::string("invalid descriptor");
    }

    descriptors.insert(descriptor);
}

void Select::removeDescriptor(Descriptors& descriptors, int descriptor)
{
    if (descriptor <= INVALID_DESCRIPTOR)
    {
        throw std::string("invalid descriptor");
    }

    descriptors.erase(descriptor);
}

int Select::max(int a, int b) const
{
    return
        a > b ? a : b;
}

} /* namespace Flix */
