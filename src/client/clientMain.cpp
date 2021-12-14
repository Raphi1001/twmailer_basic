#include "client.h"
#include "message.h"

int main(int argc, char *argv[])
{
    Client client;

    client.userLogin();
    client.startOption(client.getOptions());
    

    return 0;
}