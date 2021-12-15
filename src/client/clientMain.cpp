#include "client.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
    Client client;
    SendOption input;

    client.readInput(argc, argv);
    client.setupSocket();

    client.userLogin();
    while ((input = client.getOptions()) != QUIT || client.getSocket_fd() < 1)
    {
        client.startOption(input);
    }

    if(client.getSocket_fd() < 1)
    {
        std::cout << "Verbindung zum Server verloren";
    }

    return 0;
}