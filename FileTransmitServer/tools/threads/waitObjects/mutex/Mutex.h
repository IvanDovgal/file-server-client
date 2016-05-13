//
// Created by ivan on 20.03.16.
//

#ifndef FILETRANSMITSERVER_MUTEXT_H
#define FILETRANSMITSERVER_MUTEXT_H

#include <pthread.h>


/*
 * С++ обертка над POSIX pthread_mutex
 */
class Mutex {
protected:
    pthread_mutex_t mutex_t;
public:
    Mutex(bool locked);
    ~Mutex();
    /*
     * Переводит мьютекс в отмеченное состояние
     */
    void lock();
    /*
     * Попытка перевести мьютекс в отмеченное состояние
     */
    void tryLock();
    /*
     * Снимает отмеченное состояние
     */
    void unlock();
};


#endif //FILETRANSMITSERVER_MUTEXT_H
