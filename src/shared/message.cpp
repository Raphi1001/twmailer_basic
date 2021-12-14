#include "message.h"

using namespace std;

Message::Message()
{
}

bool Message::setMessageNumber(int messageNumber)
{
    // ToDO: set messageNumber correctly

    this->messageNumber = messageNumber;
    return true;
}

bool Message::setSender(string sender)
{
    if (!checkMaxSize(sender, 8) || !isDigitLetterOnly(sender))
        return false;

    this->sender = sender;
    return true;
}

bool Message::setReciever(string reciever)
{
    if (!checkMaxSize(reciever, 8) || !isDigitLetterOnly(reciever))
        return false;

    this->reciever = reciever;
    return true;
}

bool Message::setSubject(string subject)
{
    if (!checkMaxSize(reciever, 80) || !isDigitLetterOnly(reciever))
        return false;

    this->subject = subject;
    return true;
}

bool Message::setMessageContent(string messageContent)
{
    if (!isDigitLetterOnly(messageContent))
        return false;

    this->messageContent = messageContent;
    return true;
}

void Message::setMessageHead(SendOption messageHead)
{
    switch(messageHead)
    {
        case SEND:
            this->messageHead = "SEND\n";
            break;

        case LIST:
            this->messageHead = "LIST\n";
            break;

        case READ:
            this->messageHead = "READ\n";
            break;

        case DEL:
            this->messageHead = "DEL\n";
            break;

        case QUIT:
            this->messageHead = "QUIT\n";
            break;

        default:
            this->messageHead = "";
            break;
    }
}

int Message::getMessageNumber()
{
    return messageNumber;
}
std::string Message::getSender()
{
    return sender;
}
std::string Message::getReciever()
{
    return reciever;
}
std::string Message::getSubject()
{
    return subject;
}
std::string Message::getMessageContent()
{
    return messageContent;
}
std::string Message::getMessageString()
{
    return messageString;
}

// prüft ob ein string eine gegebene Maximallänge nicht überschreitet
bool Message::checkMaxSize(string word, int max)
{
    if ((int)word.size() > max)
        return false;

    return true;
}

// prüft ob ein string nur aus buchstaben und zahlen besteht
bool Message::isDigitLetterOnly(string word)
{
    for (int i = 0; i < (int)word.size(); i++)
    {
        if (!isdigit(word.at(i)) && !isalpha(word.at(i)))
            return false;
    }
    return true;
}

void Message::loadMessage(std::string msgPath)
{
    ifstream input_file(msgPath);

    if (!input_file.is_open())
    {
        cerr << "File konnte nicht geöffnet werden: " << msgPath << endl;
        exit(EXIT_FAILURE);
    }

    string currentLine;
    getline(input_file, currentLine);
    char *end;
    setMessageNumber(strtod(currentLine.c_str(), &end));

    getline(input_file, currentLine);
    setSender(currentLine);

    getline(input_file, currentLine);
    setReciever(currentLine);

    getline(input_file, currentLine);
    setSubject(currentLine);

    getline(input_file, currentLine);
    setMessageContent(currentLine);

    input_file.close();
}

void Message::cleanMsg()
{
    messageHead = "";
    reciever = "";
    subject = "";
    messageContent = "";
    messageNumber = -1;
    messageString = "";
}

void Message::createMsgString()
{
    messageString = messageHead;

    if(sender != "")
        messageString += sender + "\n";

    if(reciever != "")
        messageString += reciever + "\n";

    if(subject != "")
        messageString += subject + "\n";

    if(messageContent != "")
        messageString += messageContent + "\n";

    if(messageNumber != -1)
        messageString += to_string(messageNumber) + "\n";

    messageString += ".\n";
}