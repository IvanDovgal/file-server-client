//
// Created by ivan on 20.03.16.
//

#ifndef FILETRANSMITSERVER_REQUESTQUEUE_H
#define FILETRANSMITSERVER_REQUESTQUEUE_H

#include <queue>
#include "../tools/log/Log.h"
#include "../tools/threads/waitObjects/mutex/Mutex.h"
#include "../tools/threads/waitObjects/conditionalVariable/Signal.h"


/*
 * Потоко-безопасная очередь подключений
 */
class RequestQueue {
private:
    Signal *emptySignal = new Signal();
    Mutex *queueMutex = new Mutex(false);

    int size, count;
    Log *log = new Log("RequestQueue");
    std::queue<int> queue;
public:
    /*
     * Конструктор, параметр -- вместимость очереди
     */
    RequestQueue(int size);
    ~RequestQueue();
    /*
     * Добавляет подключение в очередь
     */
    bool enqueue(int socket);
    /*
     * Извлекает подключение из очереди, если очередь пуста, вызывающий поток засыпает до добавления элемента в очередь
     */
    int dequeue();
    /*
     * Возвращает количество свободных мест в очереди
     */
    int avaiable();
};

#endif //FILETRANSMITSERVER_REQUESTQUEUE_H
