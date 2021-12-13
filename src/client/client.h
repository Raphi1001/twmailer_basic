#include <netinet/in.h>
#include <iostream>

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
        struct  sockaddr_in server_addr;
};