#ifndef REQUESTHANDLER_H
#define REQUESTHANDLER_H
#include "request.h"
#include "response.h"
#include "runnable.h"
#include "abstractbuffer.h"

class RequestHandler : public Runnable
{
private:
    Request request;
    AbstractBuffer<Request> *responses;
    bool hasDebugLog;
    QString id_;

public:
    RequestHandler(Request request, AbstractBuffer<Request> *responses, bool hasDebugLog): request(request), responses(responses), hasDebugLog(hasDebugLog) {}
    void run() override;
    QString id() override;
    Response handle();
};

#endif // REQUESTHANDLER_H
