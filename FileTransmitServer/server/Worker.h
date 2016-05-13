//
// Created by ivan on 20.03.16.
//

#ifndef FILETRANSMITSERVER_WORKER_H
#define FILETRANSMITSERVER_WORKER_H


#include "../tools/threads/Thread.h"
#include "../tools/log/Log.h"
#include "../tools/threads/waitObjects/conditionalVariable/Signal.h"
#include <functional>

/*
 * Абстрактный поток -- обработчик соединений
 */
class Worker : public Thread {
private:
public:
    virtual void run() override;

    virtual void callback() override;
    std::function<void(Worker *)> _callback;
    void retrieve();
    Log *log = new Log("Worker");
    Signal *condVar = new Signal();
    Mutex *handleMutex = new Mutex(false);
    int socket;
    bool stopped = false;
public:
    ~Worker();

protected:
    virtual void process(int socket);
public:
    /*
     * Конструктор, параметр -- функция возвращающая данный поток обратно в стек
     */
    Worker(std::function<void(Worker *)> _callback);
    /*
     * Останавливает обработчик
     */
    void stop();

    /*
     * Обрабатывает подключение в отдельном потоке
     */
    void handle(int socket);
};


#endif //FILETRANSMITSERVER_WORKER_H
