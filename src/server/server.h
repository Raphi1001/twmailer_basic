#ifndef SERVER_H
#define SERVER_H

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

#include "database.h"
#include "user.h"
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
    char dataSending[2048];
    char dataReceived[2048];
    int connectionCode;
    int clientConnect;
    int clientList;
    struct sockaddr_in my_addr;

    void print_usage();
    void reciveClient();

    void quitClient(std::string client);
};

#endif
