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
        SendOption getOptions();
        void startOption(SendOption input);
        void userLogin();

        int getSocket_fd(){return socket_fd;}


private:
    void print_usage();
    void readServer();
    void sendServer();
    void setSEND();
    void setMsgNrClient();
    void waitServerRespons();

    std::string ip_s;
    uint16_t port;
    int n;
    int socket_fd;
    int connectionCode;
    char dataSending[2048] = "Test";
    struct sockaddr_in server_addr;
    Message msg;
};
#endif