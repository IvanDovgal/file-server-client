//
// Created by ivan on 20.03.16.
//

#include "RequestQueue.h"
#include <queue>
RequestQueue::RequestQueue(int size) {
    this->size = size;
    this->count = 0;
}

RequestQueue::~RequestQueue() {
    delete emptySignal;
    delete queueMutex;
    delete log;
}

bool RequestQueue::enqueue(int socket) {
    emptySignal->lock();
    bool val = true;
    bool empty = count == 0;
    queueMutex->lock();
    if(count < size)
        queue.push(socket);
    else
        val = false;
    count++;
    queueMutex->unlock();
    //Если была пуста меняет состояние условной переменной, тем самым отправляя событие заснувшему потоку
    if(empty)
        emptySignal->send();
    emptySignal->unlock();
}

int RequestQueue::dequeue() {
    emptySignal->lock();
    //Если очередь пуста, поток засыпает
    if(count==0)
        emptySignal->wait();
    queueMutex->lock();
    int val = queue.front();
    queue.pop();
    count--;
    queueMutex->unlock();
    emptySignal->unlock();
    return val;
}

int RequestQueue::avaiable() {
    return size - count;
}



