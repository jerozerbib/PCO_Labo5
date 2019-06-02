#include <iostream>

#include "requestthread.h"
#include "requesthandler.h"

void RequestThread::run()
{
    runnable->run();
    hasFinished(this);
}

RequestThread::~RequestThread()
{
    std::cout << "Killing a thread" << std::endl;
}

void RequestThread::setRunnable(Runnable *runnable) {
    this->runnable = runnable;
}
