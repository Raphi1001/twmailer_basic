#include "client.h"

/// Helperfunc
void Client::print_usage()
{
    std::cout << "Usage: ./twmailer-server <port> <mail-spool-directoryname>" << std::endl;
    exit(EXIT_FAILURE);
}

/// RichtierCode

void Client::readInput(int argc, char *argv[])
{
    int c;
    bool error = false;

    std::string program_name = argv[0];

    while ((c = getopt(argc, argv, ":")) != EOF && !error)
    {
        switch (c)
        {
        case '?':
            error = true;
            break;

        default:
            assert(0);
            break;
        }
    }

    if (error || argc < optind + 2)
    {
        print_usage();
        exit(EXIT_FAILURE);
    }

    try
    {
        ip_s = argv[optind];
        optind++;
        std::string port_s(argv[optind]);
        port = std::stoi(port_s);
    }
    catch (...)
    {
        print_usage();
        exit(EXIT_FAILURE);
    }
}

void Client::setupSocket()
{
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&server_addr, 0, sizeof(server_addr));
    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(port);
    server_addr.sin_addr.s_addr = inet_addr(ip_s.c_str());

    connectionCode = connect(socket_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    if (connectionCode == -1)
    {
        perror("bind error");
        exit(EXIT_FAILURE);
    }
}

void Client::userLogin()
{
    std::string s;

    std::cout << "Username: ";
    std::cin >> s;

    while (!msg.setSender(s))
    {
        std::cout << "Ungültige Eingabe, versuch es erneut: ";
        s = "";
        std::cin >> s;
    }
}

ClientOption Client::getOptions()
{
    char option;

    std::cout << "Optionen: " << std::endl 
    << "  (1) SEND" << std::endl 
    << "  (2) LIST" << std::endl 
    << "  (3) READ" << std::endl 
    << "  (4) DEL" << std::endl 
    << "  (5) QUIT" << std::endl 
    << std::endl << "Deine Eingabe: ";

    do
    {
        std::cin >> option;
    }while(option < 49 || option > 53);

    switch(option)
    {
        case '1':
            return ClientOption.SEND;

        case '2':
            return ClientOption.LIST;
        break;

        case '3':
            return ClientOption.READ;
        break;

        case '4':
            return ClientOption.DEL;
        break;

        case '5':
            return ClientOption.QUIT;
        break;
    }
    return ClientOption.QUIT;
}

void Client::startOption(){

}

void Client::sendSend()
{

}