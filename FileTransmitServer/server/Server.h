//
// Created by ivan on 20.03.16.
//

#ifndef FILETRANSMITSERVER_SERVER_H
#define FILETRANSMITSERVER_SERVER_H


#include <map>
#include "../tools/threads/waitObjects/mutex/Mutex.h"
#include "RequestQueue.h"
#include "Worker.h"
#include "AcceptorThread.h"

/*
 * Класс, реализация сервера
 * В отдельном потоке слушает сокет, и при подключениие клиента кладет его в AcceptorThread
 */
class Server : public Thread {
private:
protected:
    virtual void callback() override;

    void load();
    void unload();
    Worker* getWorker();
    std::vector<Worker*> workers;
    unsigned short port;
    std::queue<Worker*> threadPool;
    int threadCount;
    Signal *signal = new Signal();
    RequestQueue * requestQueue;
    Log *log = new Log("Server");
    AcceptorThread *acceptorThread;
    std::map<int, struct sockaddr_in> clients;
public:
    /*
     * Конструктор, параметры -- порт, количество потоков, размер очереди подключений
     */
    Server(unsigned short port, int threadCount, int requestQueueSize);
    ~Server();
    /*
     * Запуускает сервера
     */
    void start();
    /*
     * Останавливает сервер
     */
    void stop();

    bool stopped = false;
    int server_socket;
};


#endif //FILETRANSMITSERVER_SERVER_H
