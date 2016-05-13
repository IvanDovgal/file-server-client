//
// Created by ivan on 21.03.16.
//

#ifndef FILETRANSMITSERVER_FILERECEIVEWORKER_H
#define FILETRANSMITSERVER_FILERECEIVEWORKER_H


#include "Worker.h"

/*
 * Реализация Worker для приема файлов
 */
class FileReceiveWorker : public Worker {

public:
    FileReceiveWorker(const std::function<void(Worker *)> &_callback) : Worker(_callback) { }

protected:
    virtual void process(int socket) override;
};


#endif //FILETRANSMITSERVER_FILERECEIVEWORKER_H
