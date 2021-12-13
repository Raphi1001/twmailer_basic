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
        char dataSending[2048];
        char dataReceived[2048];
        int connectionCode;
        int clientConnect;
        int clientList;
        struct sockaddr_in my_addr;

        void print_usage();
        void reciveClient();
};