#include <netinet/in.h>
#include <iostream>

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
};