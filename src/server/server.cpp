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

        while (clientConnect > 0)
        {
            msg.cleanMsg();
            if (msg.setMessageHead(reciveClient()))
                workWithMsgHead();
            else
                sendAnswer(false);
        }

        close(clientConnect);
    }
}

std::string Server::reciveClient()
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

    tmp.pop_back();
    std::cout << tmp << std::endl;
    return tmp;
}

// nimmt keinen switch
void Server::workWithMsgHead()
{
    if (msg.getMessageHead() == "SEND")
    {
        setMsgSEND();
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
    else if (msg.getMessageHead() == "LIST")
    {
        setUser();
        database.getUser(msg.getSender())->getAllMessages();
        sendAnswer(true);
    }
    else if (msg.getMessageHead() == "READ")
    {
        setUser();
        setMsgNr();
        Message *answere = database.getUserMessage(msg.getSender(), msg.getMessageNumber());
        if (answere)
        {
            sendReadAnswer(answere->getSender());
            sendReadAnswer(answere->getReceiver());
            sendReadAnswer(answere->getSubject());
            sendReadAnswer(answere->getMessageContent());
        }
        else
        {
            std::cout << "Fehler" << std::endl;
            sendAnswer(false);
        }
    }
    else if (msg.getMessageHead() == "DEL")
    {
        setUser();
        setMsgNr();
        if (database.deleteUserMessage(msg.getSender(), msg.getMessageNumber()))
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
    if (answer)
        snprintf(dataSending, sizeof(dataSending), "OK\n");
    else
        snprintf(dataSending, sizeof(dataSending), "ERR\n");

    write(clientConnect, dataSending, strlen(dataSending));
}

void Server::setMsgSEND()
{
    if (
        msg.setSender(reciveClient()) &&
        msg.setReceiver(reciveClient()) &&
        msg.setSubject(reciveClient()) &&
        msg.setMessageContent(reciveClient()) &&
        reciveClient() == ".")
        std::cout << "Msg wurde erfolgreich verarbeitet" << std::endl;
    else
        std::cout << "Msg wurde nicht erfolgreich verarbeitet" << std::endl;
}

void Server::setMsgNr()
{
    try
    {
        if (!msg.setMessageNumber(stoi(reciveClient())))
            std::cout << "MsgNr wurde nicht erfolgreich verarbeitet" << std::endl;
    }
    catch (...)
    {
        std::cout << "Msg wurde nicht erfolgreich verarbeitet" << std::endl;
    }
}

void Server::setUser()
{
    if (!msg.setSender(reciveClient()))
        std::cout << "Sender wurde nicht erfolgreich verarbeitet" << std::endl;
}

void Server::sendReadAnswer(std::string str)
{
    int i;
    std::cout << str << std::endl;

    if ((i = send(clientConnect, str.c_str(), sizeof(str), 0)) == -1)
    {
        std::cout << "Fehler beim senden!" << std::endl;
        exit(EXIT_FAILURE);
    }
    sleep(1);
    i == -1 ? std::cout << "Senden war nicht erfolgreich!" << std::endl : std::cout << "Senden war erfolgreich!" << std::endl;
}