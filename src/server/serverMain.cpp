#include "server.h"
#include "database.h"

int main(int argc, char *argv[])
{
    Server server;

    server.readInput(argc, argv);
    server.setupSocket();

    Database testDatabase;

    testDatabase.setDir("moin");

    ////DELETE////
    /*if (testDatabase.deleteUserMessage("popo", 2))
        std::cout << "gelöscht" << std::endl;
         else
        std::cout << "nicht gelöscht" << std::endl;
    */

    /// SEND
    /*
        if (testDatabase.sendMessage("harry", "po", "Geburtstagspartyyyy", "Ichliebediir"))
            std::cout << "ok" << std::endl;
        else
            std::cout << "nicht ok" << std::endl;
    */
    //// READ
    /*
    Message *testMessage = testDatabase.getUserMessage("harry123", 0);
    if (testMessage)
        std::cout << testMessage->getSubject() << std::endl;
    else
        std::cout << "Fehler" << std::endl;
    */
    //// LIST
    /*
    testDatabase.getUser("popo");
    */
    testDatabase.printAllUsers();

    server.listenToClient();
}