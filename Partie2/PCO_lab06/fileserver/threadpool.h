#ifndef THREADPOOL_H
#define THREADPOOL_H

#include "runnable.h"
#include "requestthread.h"
#include "QObject"
#include <unistd.h>


class ThreadPool : public QObject
{
    Q_OBJECT
private:
    std::vector<RequestThread *> availableThreads;
    std::vector<RequestThread *> occupiedThreads;

    int maxThreadCount, threadCount;
    bool hasDebugLog;
public:
    explicit ThreadPool(int maxThreadCount, bool hasDebugLog = true);

    /* Start a runnable. If a thread in the pool is available, handle
       the runnable with it. If no thread is available but the pool can
       grow, create a new pool thread and handle the runnable with it. If
       no thread is available and the pool is at max capacity, block the
       caller until a thread becomes available again. */
    void start(Runnable* runnable);

    ~ThreadPool();
public slots:
    static void hasFinished(RequestThread * thread);
};

#endif // THREADPOOL_H
