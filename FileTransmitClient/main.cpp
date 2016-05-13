#include <iostream>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <cstring>

using namespace std;

const unsigned int MAGIC_SERVER = 0xFF00F0C0;
const unsigned int MAGIC_CLIENT = 0xF0F0FA80;

unsigned int min(unsigned int a, unsigned int b) {
    return a > b ? b : a;
}

int main(int argc, char **args) {
    int port = atoi(args[2]);
    sockaddr_in dest_addr;
    int server_socket;
    server_socket = socket(AF_INET, SOCK_STREAM, 0);
    dest_addr.sin_family = AF_INET;
    dest_addr.sin_port = htons(port);
    dest_addr.sin_addr.s_addr = inet_addr(args[1]);
    FILE *file = fopen(args[1], "r");
    fseek(file, 0L, SEEK_END);
    unsigned int filesize = (unsigned int) ftell(file);
    fseek(file, 0L, SEEK_SET);
    char buf[256];
    connect(server_socket, (sockaddr *) &dest_addr, sizeof(dest_addr));
    unsigned int handshake;
    cout << "Checking server" << endl;
    read(server_socket, &handshake, 4);
    if (handshake == MAGIC_SERVER) {
        cout << "Server valid" << endl;
        write(server_socket, &MAGIC_CLIENT, 4);
        int length = (int) strlen(args[1]);
        write(server_socket, &length, 4);
        write(server_socket, args[1], length);
        write(server_socket, &filesize, 4);
        while (filesize > 0) {
            int size = min(256, filesize);
            filesize -= fread(buf, 1, size, file);
            write(server_socket, buf, size);
        }
    } else cout << "Server invalid" << endl;
    close(server_socket);
    fclose(file);

    return 0;
}