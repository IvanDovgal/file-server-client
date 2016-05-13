//
// Created by ivan on 20.03.16.
//

#include <pthread.h>
#include "Signal.h"


Signal::Signal() : Mutex(false) {
    pthread_mutex_init(&mutex_t, nullptr);
    pthread_cond_init(&cond_t, nullptr);
}

void Signal::wait() {
    pthread_cond_wait(&cond_t, &mutex_t);
}

void Signal::send() {
    pthread_cond_signal(&cond_t);
}

