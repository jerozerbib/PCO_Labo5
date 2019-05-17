#ifndef MESSAGEBUFFER_H
#define MESSAGEBUFFER_H

#include "abstractbuffer.h"

#include <QMutex>
#include <QWaitCondition>

template<typename T>
class MessageBuffer: public AbstractBuffer<T>
{
public:
    MessageBuffer(unsigned int size) : buffer(new T[size]), size(size), nbItems(0), currentWritePos(0), currentReadPos(0) {}

    void put(T item) {
        mutex.lock();

        while(nbItems >= size)
            hasSpace.wait(&mutex);

        buffer[currentWritePos] = item;
        currentWritePos = ++currentWritePos % size;
        ++nbItems;
        hasItem.wakeOne();

        mutex.unlock();
    }

    T get() {
        T item;
        mutex.lock();

        while(nbItems == 0)
            hasItem.wait(&mutex);

        item = buffer[currentReadPos];
        currentReadPos = ++currentReadPos % size;
        --nbItems;

        mutex.unlock();
        hasSpace.wakeOne();

        return item;
    }

private:
    T *buffer;
    unsigned int size;
    unsigned int nbItems;

    unsigned int currentWritePos;
    unsigned int currentReadPos;

    QWaitCondition hasSpace, hasItem;
    QMutex mutex;
};

#endif // MESSAGEBUFFER_H
