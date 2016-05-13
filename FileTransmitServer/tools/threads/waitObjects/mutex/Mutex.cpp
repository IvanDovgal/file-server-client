//
// Created by ivan on 20.03.16.
//

#include "Mutex.h"
#include <pthread.h>
Mutex::Mutex(bool locked) {
    mutex_t = PTHREAD_MUTEX_INITIALIZER;
    if(locked)
        lock();
}


void Mutex::lock() {
    pthread_mutex_lock(&mutex_t);
}

void Mutex::tryLock() {
    pthread_mutex_trylock(&mutex_t);
}

void Mutex::unlock() {
    pthread_mutex_unlock(&mutex_t);
}

Mutex::~Mutex() {
    pthread_mutex_destroy(&mutex_t);
}



