//
// Created by ivan on 20.03.16.
//

#include <functional>
#include "Worker.h"
#include "Server.h"


Worker::Worker(std::function<void(Worker *)> callback) {
    this->_callback = callback;
}

void Worker::retrieve() {
    _callback(this);
}

void Worker::callback() {
    auto flag = true;
    while(flag) {
        condVar->lock();
        condVar->wait();
        if(!stopped) {
            process(socket);
            close(socket);
            retrieve();
        }
        flag = !stopped;
        condVar->unlock();
    }
}

void Worker::run() {
    retrieve();
    Thread::run();
}


void Worker::handle(int socket) {

    //handleMutex->lock();
    condVar->lock();
    this->socket = socket;
    condVar->send();
    condVar->unlock();
    //handleMutex->unlock();
}

void Worker::stop() {
    condVar->lock();
    this->stopped = true;
    condVar->send();
    condVar->unlock();
}

Worker::~Worker() {
    stop();
    delete log;
    delete condVar;
    delete handleMutex;
}

void Worker::process(int socket) {

}






