#ifndef NETWORKING_SELECT_H_
#define NETWORKING_SELECT_H_

#include <unistd.h>
#include <set>
#include <string>

namespace Flix {

typedef std::set<int> Descriptors;

class Select {
public:
    Select();
    virtual ~Select();

    int execute(void);

    void addReadDescriptor(int descriptor);
    void removeReadDescriptor(int descriptor);
    void addWriteDescriptor(int descriptor);
    void removeWriteDescriptor(int descriptor);

    size_t getReadDescriptorCount(void) const;
    size_t getWriteDescriptorCount(void) const;

    bool readDescriptorIsSet(int descriptor) const;
    bool writeDescriptorIsSet(int descriptor) const;

    void setTimeout(timeval& timeout);
    void setTimeout(time_t timeoutSeconds);
    void setTimeout(time_t timeoutSeconds, useconds_t timeoutMicroseconds);
    const timeval& getTimeout(void) const;
    const timeval& getRemainingTime(void) const;

    void setAutoReloadTimeout(bool enable);
    bool getAutoReloadTimeout(void) const;

    void reloadTimeout(void);

private:
    fd_set selectReadDescriptors;
    fd_set selectWriteDescriptors;
    Descriptors readDescriptors;
    Descriptors writeDescriptors;

    timeval defaultTimeout;
    timeval timeout;
    bool autoReloadTimeout;

    void addDescriptor(Descriptors& descriptors, int descriptor);
    void removeDescriptor(Descriptors& descriptors, int descriptor);
    int max(int a, int b) const;
};

} /* namespace Flix */

#endif /* NETWORKING_SELECT_H_ */
