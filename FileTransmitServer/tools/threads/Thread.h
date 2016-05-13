//
// Created by ivan on 20.03.16.
//

#ifndef FILETRANSMITSERVER_THREAD_H
#define FILETRANSMITSERVER_THREAD_H

#include <pthread.h>

/**
 * POSIX -- стандарт для языка C
 * Это C++ обертка над posix_thread
 */
class Thread {
private:
    pthread_t thread;
public:
    Thread();
    /*
     * Виртуальный метод, реализация данного метода в классах-наследниках будет выполнена в отдельном потоке
     */
    virtual void callback();
    /*
     * Запуск потока
     */
    virtual void run();
    /*
     * Присоединение потока
     */
    void join();
    /*
     * Прервать выполнение потока
     */
    void interrupt();
};

#endif //FILETRANSMITSERVER_THREAD_H
