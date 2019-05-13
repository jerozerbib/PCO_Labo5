#ifndef MESSAGEBUFFER_H
#define MESSAGEBUFFER_H

#include "abstractbuffer.h"

#include <QMutex>
#include <QSemaphore>

template<typename T>
class MessageBuffer: public AbstractBuffer<T>
{
public:
    MessageBuffer(unsigned int size) : buffer(new T[size]), size(size), currentWritePos(0), currentReadPos(0), waitSpace(static_cast<int>(size)){}

    void put(T item) {
        waitSpace.acquire();
        waitWrite.lock();

        buffer[currentWritePos] = item;
        currentWritePos = ++currentWritePos % size;

        waitItem.release();
        waitWrite.unlock();
    }

    T get() {
        waitRead().lock();
        waitItem.acquire();

        T item = buffer[currentReadPos];
        currentReadPos = ++currentReadPos % size;

        waitSpace.release();
        waitRead().unlock();

        return item;
    }

private:
    T *buffer;
    unsigned int size;

    unsigned int currentWritePos;
    unsigned int currentReadPos;

    QSemaphore waitSpace;
    QSemaphore waitItem;
    QMutex waitWrite;
    QMutex waitRead;
};

#endif // MESSAGEBUFFER_H
