#include "client.h"
#include "message.h"
#include <unistd.h>

int main(int argc, char *argv[])
{
    Client client;
    ClientOption input;

    client.userLogin();
    while((input = client.getOptions()) != QUIT)
    {
        client.startOption(input);
    }

    return 0;
}