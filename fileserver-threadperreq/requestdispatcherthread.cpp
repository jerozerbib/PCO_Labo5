#include "requestdispatcherthread.h"
#include <QDebug>
#include <QPointer>

void RequestDispatcherThread::run()
{
    while(true) {
        if (hasDebugLog)
            qDebug() << "Waiting for responses...";
        Request req = requests->get();   // block until a response is available
        if (hasDebugLog)
            qDebug() << "Got a request'" << req.getFilePath() << "', dispatching...";
        QPointer<RequestHandler> reqHandler = new RequestHandler(req, responses, hasDebugLog);
        reqHandler->start();

        connect(reqHandler, &RequestHandler::finished, reqHandler, &QObject::deleteLater);
    }
}
