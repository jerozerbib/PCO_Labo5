#include "threadpool.h"

ThreadPool::ThreadPool(int maxThreadCount, bool hasDebugLog) : maxThreadCount(maxThreadCount), hasDebugLog(hasDebugLog){}

void ThreadPool::start(Runnable *runnable){
    while (threadCount >= maxThreadCount && availableThreads.size() == 0) {
        usleep(500);
    }

    if(availableThreads.size() != 0){
        RequestThread *req = availableThreads.at(availableThreads.size() - 1);
        occupiedThreads.push_back(req);
        availableThreads.pop_back();
        req->setRunnable(runnable);
        req->start();
    } else {
        if (threadCount < maxThreadCount){
            RequestThread *req = new RequestThread(runnable, hasDebugLog);
            connect(req, SIGNAL(hasFinished(RequestThread*)), this, SLOT(hasFinished(RequestThread*)));
            occupiedThreads.push_back(req);
            req->start();
        }
    }
}


ThreadPool::~ThreadPool(){
    for (RequestThread *req : occupiedThreads){
            req->wait();
            delete req;
    }

    for (RequestThread *req : availableThreads){
        req->wait();
        delete req;
    }


}
