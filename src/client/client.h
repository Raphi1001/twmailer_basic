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

class Client
{
public:
    void readInput(int argc, char *argv[]);
    void setupSocket();

private:
    void print_usage();
    std::string ip_s;
    uint16_t port;
    int socket_fd;
    int connectionCode;
    struct sockaddr_in server_addr;
};
#endif