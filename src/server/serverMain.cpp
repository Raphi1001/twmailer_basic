#include "server.h"

int main(int argc, char *argv[])
{
    Server server;

    server.readInput(argc, argv);
    server.setupSocket();
    server.listenToClient();



}