#include "requestdispatcherthread.h"
#include <QDebug>

void RequestDispatcherThread::run()
{
    while(true) {
        if (hasDebugLog)
            qDebug() << "Waiting for responses...";
        Request req = requests->get();   // block until a response is available
        if (hasDebugLog)
            qDebug() << "Got a request'" << req.getFilePath() << "', dispatching...";
    }
}
