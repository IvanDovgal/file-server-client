//
// Created by ivan on 21.03.16.
//

#include <sys/socket.h>
#include <netinet/in.h>
#include "AcceptorThread.h"
#include "Server.h"
#include <arpa/inet.h>


void AcceptorThread::callback() {
    //Функция, выполняющеяся в потоке, обслуживае входящие запросы
    int requestQueueSize = requestQueue->avaiable();
    while(!this->stopped) {
        int client_socket;
        struct sockaddr_in cli_addr;
        listen(server_socket, requestQueueSize);
        socklen_t clilen = sizeof(cli_addr);
        client_socket = accept(server_socket, (struct sockaddr *) &cli_addr, &clilen);
        //Если заполнена -- сбрасываем, иначе -- разрешаем
        if(requestQueue->avaiable() > 0)
        {
            try {
                log->info((std::string)"Accepted " + inet_ntoa(cli_addr.sin_addr));
                requestQueue->enqueue(client_socket);
            }
            catch(...)
            {
                return;
            }
        } else{
            close(client_socket);
            log->error((std::string)"Rejected " + inet_ntoa(cli_addr.sin_addr));
        }
    }
}

void AcceptorThread::stop() {
    this->stopped = true;
}



