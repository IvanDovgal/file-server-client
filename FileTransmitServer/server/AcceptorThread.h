//
// Created by ivan on 21.03.16.
//

#ifndef FILETRANSMITSERVER_ACCEPTORTHREAD_H
#define FILETRANSMITSERVER_ACCEPTORTHREAD_H


#include "../tools/threads/Thread.h"
#include "RequestQueue.h"


/*
 * Поток, обслуживающий подключения
 */
class AcceptorThread : public Thread {

public:
    AcceptorThread(int server_socket, RequestQueue *requestQueue) : server_socket(server_socket),
                                                                    requestQueue(requestQueue) { }
    void stop();

private:
    virtual void callback() override;
    Log *log = new Log("AcceptorThread");
    bool stopped = false;
    RequestQueue *requestQueue;

    int server_socket;
};


#endif //FILETRANSMITSERVER_ACCEPTORTHREAD_H
