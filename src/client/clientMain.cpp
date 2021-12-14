#include "client.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
    Client client;
    SendOption input;

    client.userLogin();
    while ((input = client.getOptions()) != QUIT)
    {
        client.startOption(input);
    }

    return 0;
}