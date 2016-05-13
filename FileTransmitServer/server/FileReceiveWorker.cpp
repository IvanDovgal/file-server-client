//
// Created by ivan on 21.03.16.
//

#include "FileReceiveWorker.h"


const unsigned int MAGIC_SERVER = 0xFF00F0C0;
const unsigned int MAGIC_CLIENT = 0xF0F0FA80;

const unsigned int BLOCK_SIZE = 256;
unsigned int min(unsigned int a, unsigned int b){
    return a > b ? b : a;
}
void FileReceiveWorker::process(int socket) {
    //Простое чтение данных из сокета
    write(socket, &MAGIC_SERVER, 4);
    unsigned int handshake;
    read(socket, &handshake, 4);
    if(handshake == MAGIC_CLIENT)
    {
        unsigned int filename_length;
        read(socket, &filename_length, 4);
        char *filename = new char[filename_length + 1];
        filename[filename_length] = 0;
        read(socket, filename, filename_length);
        unsigned int file_size;
        read(socket, &file_size, 4);
        unsigned int received = 0;
        char buf[BLOCK_SIZE];
        remove(filename);
        FILE *file = fopen(filename, "w");
        log->info((std::string)"Receiving file " + filename + " with size " + std::to_string(file_size));
        while(file_size > 0)
        {
            usleep(7000);
            unsigned int block_size = min(file_size, BLOCK_SIZE);
            read(socket, buf, block_size);
            fwrite(buf, 1, block_size, file);
            file_size -= block_size;
        }
        log->info((std::string)"File " + filename + " received");
        fclose(file);
    }
}

