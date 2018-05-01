#include <unistd.h>
#include <cassert>
#include <cstring>
#include <networking/utils/GenericThread.h>
#include <networking/utils/Log.h>

#define PERIODIC_TASK_INTERVAL_MIN_SECONDS (5)
#define PERIODIC_TASK_INTERVAL_DEFAULT_SECONDS (20)

namespace Flix {

GenericThread::GenericThread(const std::string& identifier, bool silent):
    identifier(identifier),
    silent(silent),
    threadFinished(false),
    genericThread(nullptr),
    periodicTaskInterval(PERIODIC_TASK_INTERVAL_DEFAULT_SECONDS)
{
    bzero(controlPipe, sizeof(controlPipe));
    assert(pipe(controlPipe) == 0);
}

GenericThread::~GenericThread()
{
    close(controlPipe[CONTROL_PIPE_OUT]);
    close(controlPipe[CONTROL_PIPE_IN]);
}

bool GenericThread::start(void)
{
    if (genericThread) {
        return false;
    }

    if (!setup()) {
        LOG_ERROR("Could not setup thread \"" << identifier << "\"");
        return false;
    }

    genericThread = new std::thread(&GenericThread::run, this);

    return true;
}

bool GenericThread::stop(void)
{
    if (!genericThread) {
        return false;
    }

    ThreadControl threadControl = ThreadControl::QUIT;
    ssize_t bytesWritten = write(controlPipe[CONTROL_PIPE_OUT], &threadControl, sizeof(threadControl));

    genericThread->join();
    delete genericThread;
    genericThread = nullptr;

    return bytesWritten > 0;
}

bool GenericThread::threadHasFinished(void) const
{
    return threadFinished;
}

bool GenericThread::periodicTask(void)
{
    return true;
}

void GenericThread::updateDescriptors(int& maxDescriptor, fd_set& descriptors, timeval& timeout)
{
}

void GenericThread::setPeriodicTaskInterval(int seconds)
{
    periodicTaskInterval = max(PERIODIC_TASK_INTERVAL_MIN_SECONDS, seconds);
}

int GenericThread::max(int a, int b) const
{
    return a > b ? a : b;
}

void GenericThread::run(void)
{
    int maxDescriptor;
    fd_set descriptors;
    timeval timeout;
    timespec lastRunPeriodicTask;

    if (!silent) LOG_INFO("Started thread \"" << identifier << "\"");

    clock_gettime(CLOCK_MONOTONIC_COARSE, &lastRunPeriodicTask);

    do {
        timeout.tv_sec = periodicTaskInterval / 2;
        timeout.tv_usec = 0;

        FD_ZERO(&descriptors);
        FD_SET(controlPipe[CONTROL_PIPE_IN], &descriptors);
        maxDescriptor = controlPipe[CONTROL_PIPE_IN];

        updateDescriptors(maxDescriptor, descriptors, timeout);

        if (select(maxDescriptor + 1, &descriptors, nullptr, nullptr, &timeout) > 0) {
            if (FD_ISSET(controlPipe[CONTROL_PIPE_IN], &descriptors)) {
                ThreadControl threadControl = ThreadControl::UNKNOWN;
                ssize_t readBytes = read(controlPipe[CONTROL_PIPE_IN], &threadControl, sizeof(ThreadControl));
                if (threadControl == ThreadControl::QUIT) {
                    if (!silent) LOG_DEBUG("Thread \"" << identifier << "\" received quit signal.");
                    break;
                } else if (threadControl == ThreadControl::TASK) {
                    if (!task(descriptors)) {
                        LOG_ERROR("Task of thread \"" << identifier << "\" failed!");
                        break;
                    }
                }
            } else {
                if (!task(descriptors)) {
                    LOG_ERROR("Task of thread \"" << identifier << "\" failed!");
                    break;
                }
            }
        }
        timespec currentTime;
        clock_gettime(CLOCK_MONOTONIC_COARSE, &currentTime);
        if (currentTime.tv_sec >= (lastRunPeriodicTask.tv_sec + periodicTaskInterval)) {
            if (!periodicTask()) {
                LOG_ERROR("Periodic task of thread \"" << identifier << "\" failed!");
                break;
            }
            lastRunPeriodicTask = currentTime;
        }
    } while (!threadFinished);

    if (!silent) LOG_INFO("Stopped thread \"" << identifier << "\"");
}

} /* namespace Flix */
