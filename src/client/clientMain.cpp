#include "client.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
    Client client;

    client.readInput(argc, argv);
    client.setupSocket();
    //client.readServer();
    client.sendServer();

    sleep(10);
    return 0;
}