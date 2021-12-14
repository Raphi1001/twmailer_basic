#include "server.h"
#include "database.h"

int main(int argc, char *argv[])
{
    Server server;

    server.readInput(argc, argv);
    server.setupSocket();

    Database testDatabase;

    testDatabase.setDir("moin");
    std::cout << testDatabase.getUsers()[0].getMessages()[0].getSubject() << std::endl;

    server.listenToClient();
}