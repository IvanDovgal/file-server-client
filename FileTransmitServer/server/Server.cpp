//
// Created by ivan on 20.03.16.
//

#include <netinet/in.h>
#include <memory.h>
#include <functional>
#include "Server.h"
#include "Worker.h"
#include "FileReceiveWorker.h"

void Server::start() {
    load();
    struct sockaddr_in serv_addr;
    int n;
    int client_socket;
    //Открываем сокет
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    log->info(std::to_string(server_socket));
    bzero((char *) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    unsigned short portno = htons(port);
    serv_addr.sin_port = portno;
    //Привязываем сокет к порту
    if (bind(server_socket, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
        log->error("Binding failed");
    run();
    // Создаем и запускаем обслуживающий поток
    acceptorThread = new AcceptorThread(server_socket, requestQueue);
    acceptorThread->run();
}

void Server::callback() {
    //Метод, выполняющийся в отдельном потоке, извлекает подключение из очереди, и обработчик из стека, и передает подклчюение на обработку обработчику
    while(true)
    {
        int socket = requestQueue->dequeue();
        if(stopped)
            return;
        Worker* worker = getWorker();
        worker->handle(socket);
    }
}


Server::Server(unsigned short port, int threadCount, int requestQueueSize) {
    this->port = port;
    this->threadCount = threadCount;
    requestQueue = new RequestQueue(requestQueueSize);
}

void Server::unload() {
    //Инициализация стека обработчиков
    for(int i = 0; i < workers.size(); i++)
    {
        delete workers[i];
    }
    workers.erase(workers.begin(), workers.end());
}

void Server::load() {
    //Инициализация стека обработчиков
    auto counter = threadCount;
    while(counter-->0)
    {
        Worker *worker = new FileReceiveWorker([this](Worker* worker) -> void
                                    {
                                        signal->lock();
                                        bool notify = threadPool.empty();
                                        this->threadPool.push(worker);
                                        if(notify)
                                            signal->send();
                                        signal->unlock();
                                    });
        worker->run();
        workers.push_back(worker);
    }
}

void Server::stop() {
    acceptorThread->stop();
    delete acceptorThread;
    close(server_socket);
}

Worker *Server::getWorker() {
    //Извлекает обработчик из стека
    Worker* worker;
    signal->lock();
    if(threadPool.empty())
        signal->wait();
    worker = threadPool.front();
    threadPool.pop();
    signal->unlock();
    return worker;
}

Server::~Server() {
    unload();
    stop();
    delete requestQueue;
    delete signal;
    delete log;
}







