#ifndef CLIENT_H
#define CLIENT_H

#include <netinet/in.h>
#include <iostream>
#include <string.h>
#include <string>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <errno.h>
#include <assert.h>
#include <exception>
#include <sstream>

#include "../shared/message.h"

class Server
{
public:
    void readInput(int argc, char *argv[]);
    void setupSocket();
    void listenToClient();

private:
    uint16_t port;
    std::string dir;
    int socket_fd;
    int connectionCode;
    struct sockaddr_in my_addr;

    void print_usage();

    void sendMessage();
};
#endif