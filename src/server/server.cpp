#include "server.h"

/// Helperfuncs

void Server::print_usage()
{
    std::cout << "Usage: ./twmailer-server <port> <mail-spool-directoryname>" << std::endl;
    exit(EXIT_FAILURE);
}

/// RichtigerCode

void Server::setupSocket()
{
    clientList = socket(AF_INET, SOCK_STREAM, 0);

    memset(&my_addr, 0, sizeof(my_addr));
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(port);
    my_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    connectionCode = bind(clientList, (struct sockaddr *)&my_addr, sizeof(my_addr));

    if (connectionCode == -1)
    {
        perror("bind error");
        exit(EXIT_FAILURE);
    }
}

void Server::readInput(int argc, char *argv[])
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
        std::string s(argv[optind]);
        port = std::stoi(s);
        optind++;
        dir = argv[optind];
    }
    catch (...)
    {
        print_usage();
        exit(EXIT_FAILURE);
    }

    database.setDir(dir);
}

void Server::listenToClient()
{
    while (connectionCode == 0)
    {

        if (listen(clientList, 1) == -1)
        {
            perror("listen error");
            exit(EXIT_FAILURE);
        }

        std::cout << "Warte auf Client" << std::endl;
        if ((clientConnect = accept(clientList, (struct sockaddr *)NULL, NULL)) == -1)
        {
            std::cout << "Es ist ein Fehler beim listen aufgetreten" << std::endl;
            exit(EXIT_FAILURE);
        }

        std::cout << "Server und Client wurden erfolgreich verbunden!" << std::endl;
        snprintf(dataSending, sizeof(dataSending), "Du wurdest erfolgreich verbunden!\n");
        write(clientConnect, dataSending, strlen(dataSending));
        sleep(1);

        while (clientConnect > 0)
        {
            msg.cleanMsg();
            reciveClient();
            workWithMsgHead();
        }

        close(clientConnect);
    }
}

void Server::reciveClient()
{
    int rec;
    std::string tmp;

    std::cout << "Warte auf Client send" << std::endl;
    do
    {
        if ((rec = recv(clientConnect, dataReceiving, sizeof(dataReceiving), 0)) == -1)
        {
            std::cout << "Es ist ein Fehler beim recive aufgetreten" << std::endl;
            break;
        }
        else if (rec == 0)
        {
            std::cout << "Remote socket wurde geschlossen" << std::endl;
            break;
        }
        else
        {
            tmp += dataReceiving;
        }
    } while (rec == 2048);

    if (!msg.setMessageHead(tmp))
        close(clientConnect);
}

// nimmt keinen switch
void Server::workWithMsgHead()
{
    if (msg.getMessageHead() == "SEND\n")
    {
        if (database.sendMessage(msg.getSender(), msg.getReceiver(), msg.getSubject(), msg.getMessageContent()))
        {
            std::cout << "ok" << std::endl;
            sendAnswer(true);
        }
        else
        {
            std::cout << "nicht ok" << std::endl;
            sendAnswer(false);
        }
    }
    else if (msg.getMessageHead() == "LIST\n")
    {
        database.getUser(msg.getReceiver())->getAllMessages();
        sendAnswer(true);
    }
    else if (msg.getMessageHead() == "READ\n")
    {
        Message *answere = database.getUserMessage(msg.getReceiver(), msg.getMessageNumber());
        if (answere)
        {
            // answere;
        }
        else
        {
            std::cout << "Fehler" << std::endl;
            sendAnswer(false);
        }
    }
    else if (msg.getMessageHead() == "DEL\n")
    {
        if (database.deleteUserMessage(msg.getReceiver(), msg.getMessageNumber()))
        {
            std::cout << "gelöscht" << std::endl;
            sendAnswer(true);
        }
        else
        {
            std::cout << "nicht gelöscht" << std::endl;
            sendAnswer(false);
        }
    }
    else
        close(clientConnect);
}

void Server::sendAnswer(bool answer)
{
    int i;
    int total = 0;
    int len = (int)sizeof(msg.getMessageString()) + 1;
    int bytesleft = len;
    std::string answer_s;

    if (answer)
        answer = "OK\n";
    else
        answer = "ERR\n";

    while (total < len)
    {
        if ((i = send(clientConnect, answer_s.c_str(), sizeof(answer_s), 0)) == -1)
        {
            std::cout << "Fehler beim senden!" << std::endl;
            exit(EXIT_FAILURE);
        }
        total += i;
        bytesleft -= i;
    }
    i == -1 ? std::cout << "Senden war nicht erfolgreich!" << std::endl : std::cout << "Senden war erfolgreich!" << std::endl;
}