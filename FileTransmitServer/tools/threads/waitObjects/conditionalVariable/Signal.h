//
// Created by ivan on 20.03.16.
//

#ifndef FILETRANSMITSERVER_SIGNAL_H
#define FILETRANSMITSERVER_SIGNAL_H


#include <zconf.h>
#include "../mutex/Mutex.h"

/*
 * C++ Обертка над pthread_cond, POSIX реализации условной переменной
 */
class Signal: public Mutex {
private:
    pthread_cond_t cond_t;
public:
    Signal();
    /*
     * Засыпает поток, до получение событие
     */
    void wait();
    /*
     * Отправляет событие спящему потоку
     */
    void send();
};


#endif //FILETRANSMITSERVER_SIGNAL_H
