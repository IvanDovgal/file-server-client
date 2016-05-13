//
// Created by ivan on 20.03.16.
//

#include "Thread.h"

void* _thread_routine(void * object)
{
    ((Thread*)object)->callback();
}

void Thread::run() {
    pthread_create(&thread, nullptr, _thread_routine, this);
}

void Thread::join() {
    pthread_join(thread, nullptr);
}

Thread::Thread() {

}

void Thread::callback() {

}

void Thread::interrupt() {
    pthread_cancel(thread);
}







