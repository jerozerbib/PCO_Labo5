#ifndef REQUESTTHREAD_H
#define REQUESTTHREAD_H
#include <QThread>
#include "request.h"
#include "response.h"
#include "runnable.h"

class RequestThread: public QThread
{
private:
    Runnable *runnable;
    bool hasDebugLog;

public:
    RequestThread(Runnable *runnable, bool hasDebugLog): runnable(runnable), hasDebugLog(hasDebugLog) {}

    virtual ~RequestThread();

    void setRunnable(Runnable *runnable);

protected:
    void run();

signals:
    static void hasFinished(QThread *thread);
};

#endif // REQUESTTHREAD_H
