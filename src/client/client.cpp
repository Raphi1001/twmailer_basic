#include "client.h"

/// Helperfunc
void Client::print_usage()
{
    std::cout << "Usage: ./twmailer-client <ip> <port>" << std::endl;
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
        std::cout << "Ungültige Eingabe, keine Sonderzeichen und weniger als 8 Zeichen: ";
        s = "";
        std::cin >> s;
    }
}

SendOption Client::getOptions()
{
    std::string option;

    std::cout << std::endl
    << "Optionen: " << std::endl 
    << "  (1) SEND" << std::endl 
    << "  (2) LIST" << std::endl 
    << "  (3) READ" << std::endl 
    << "  (4) DEL" << std::endl 
    << "  (5) QUIT" << std::endl 
    << std::endl << "Deine Eingabe: ";
    std::cin >> option;

    while( option.length() != 1 || option[0] < 49 || option[0] > 53)
    {
        std::cout << "Keine Gültige Option: ";
        std::cin >> option;
    }
    
    switch(option[0])
    {
        case '1':
            return SendOption::SEND;

        case '2':
            return SendOption::LIST;

        case '3':
            return SendOption::READ;

        case '4':
            return SendOption::DEL;

        case '5':
            return SendOption::QUIT;
    }
    return SendOption::QUIT;
}

void Client::startOption(SendOption input)
{
    msg.cleanMsg();

    switch(input)
    {
        case SEND:
            setSEND();
            break;

        case LIST:
            setLIST();
            break;

        case READ:
            setREAD();
            break;

        case DEL:
            setDEL();
            break;

        case QUIT:
            setQUIT();
            break;
    }

    msg.createMsgString();
    sendServer();
}

void Client::setSEND()
{
    std::string tmp;

    std::cout << "Empfänger: ";
    std::cin >> tmp;
    while(!msg.setReciever(tmp))
    {
        std::cout << "Ungültige Eingabe, versuche es erneut: ";
        std::cin >> tmp;
    }

    tmp = "";

    std::cout << "Betreff: ";
    std::cin >> tmp;
    while(!msg.setSubject(tmp))
    {
        std::cout << "Ungültige Eingabe, versuche es erneut: ";
        std::cin >> tmp;
    }

    tmp = "";

    std::cout << "Nachricht: ";
    std::cin >> tmp;
    while(!msg.setMessageContent(tmp))
    {
        std::cout << "Ungültige Eingabe, versuche es erneut: ";
        std::cin >> tmp;
    }
}

void Client::readServer()
{
    int total = 0;
    int i;
    int len = (int)sizeof(dataSending) + 1;
    int bytesleft = len;

    while (total < len)
    {
        send(socket_fd, msg.getSender().c_str(), sizeof(msg.getSender()), 0);

        if((i = send(socket_fd, dataSending+total, bytesleft, 0)) == -1)
        {
            std::cout << "Fehler beim senden!" << std::endl;
            exit(EXIT_FAILURE);
        }
        total += i;
        bytesleft -= i;
    }
}
