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
        //handlers.push_back(reqHandler);

        connect(reqHandler, &RequestHandler::finished, reqHandler, &QObject::deleteLater);
        /*for(auto it = handlers.begin(); it != handlers.end();) {
            auto nextIt = std::next(it);
            if((*it)->isFinished()) {
                (*it)->wait();
                delete *it;
                handlers.erase(it);
            }
            it = nextIt;
        }*/
    }
}
