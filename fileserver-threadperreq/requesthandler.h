#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H
#include "request.h"
#include "response.h"

#include <QThread>

class RequestHandler : public QThread
{
private:
    Request request;
    bool hasDebugLog;

public:
    RequestHandler(Request request, bool hasDebugLog): request(request), hasDebugLog(hasDebugLog) {}

    Response handle();
    void run();

signals:
    void requestHandled();
};

#endif // REQUESTHANDLER_H
