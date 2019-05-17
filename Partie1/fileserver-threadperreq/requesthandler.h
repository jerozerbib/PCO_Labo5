#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H
#include "request.h"
#include "response.h"
#include "messagebuffer.h"

#include <QThread>
#include <QObject>

class RequestHandler : public QThread
{
    Q_OBJECT
private:
    Request request;
    AbstractBuffer<Response>* responses;
    bool hasDebugLog;
    void run();

public:
    RequestHandler(Request request, AbstractBuffer<Response>* responses, bool hasDebugLog): request(request), responses(responses), hasDebugLog(hasDebugLog) {}

    Response handle();
};

#endif // REQUESTHANDLER_H
