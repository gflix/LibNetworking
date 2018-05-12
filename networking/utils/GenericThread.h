#ifndef SRC_GENERICTHREAD_H_
#define SRC_GENERICTHREAD_H_

#include <thread>
#include <networking/Select.h>

#define CONTROL_PIPE_OUT (1)
#define CONTROL_PIPE_IN (0)

namespace Flix {

enum class ThreadControl {
    UNKNOWN,
    QUIT,
    TASK
};

class GenericThread {
public:
    GenericThread(const std::string& identifier, bool silent = false);
    virtual ~GenericThread();

    bool start(void);
    bool stop(void);
    bool runTask(void);

    bool threadHasFinished(void) const;

protected:
    std::string identifier;
    bool silent;
    int controlPipe[2];
    bool threadFinished;
    std::thread* genericThread;
    int periodicTaskInterval;

    virtual bool setup(void) = 0;
    virtual bool task(const Select& select) = 0;
    virtual bool periodicTask(void);
    virtual void updateDescriptors(Select& select);
    void setPeriodicTaskInterval(int seconds);

    int max(int a, int b) const;

private:
    void sendSignal(ThreadControl threadControl);
    virtual void run(void);
};

} /* namespace Flix */

#endif /* SRC_GENERICTHREAD_H_ */
