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
#include "../shared/message.h"

class Client
{
    public:
        void readInput(int argc, char *argv[]);
        void setupSocket();
        void setSEND();
        void setLIST();
        void setREAD();
        void setDEL();
        void setQUIT();
        void userLogin();
        SendOption getOptions();
        void startOption(SendOption input);

    private:
        void print_usage();
        void readServer();
        void sendServer();

        std::string ip_s;
        uint16_t port;
        int n;
        int socket_fd;
        int connectionCode;
        char dataSending[2048] = "Test";
        char dataReceived[2048];
        struct  sockaddr_in server_addr;
        Message msg;
};
#endif