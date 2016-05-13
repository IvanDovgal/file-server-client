#define demo

#include <iostream>
#include "tools/log/Log.h"
#include "server/Server.h"

using namespace std;



int main(int argc, char **args) {

    Server *server = new Server((unsigned short) atoi(args[1]), atoi(args[2]), atoi(args[2]));
    try{
        Log::setLevel(Log::LEVEL_ALL);
        server->start();
        server->join();
    }
    catch(...)
    {
        delete server;
        return 0;
    }
    delete server;
    return 0;
}