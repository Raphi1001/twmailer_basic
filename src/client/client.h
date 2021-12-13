#include <netinet/in.h>
#include <iostream>

class Client
{
    public:
        void readInput(int argc, char *argv[]);
        void setupSocket();
        void readServer();
        void sendServer();

    private:
        void print_usage();
        std::string ip_s;
        uint16_t port;
        int n;
        int socket_fd;
        int connectionCode;
        char dataSending[2048] = "Test";
        char dataReceived[2048];
        struct  sockaddr_in server_addr;
};