#include "message.h"

using namespace std;

Message::Message()
{
}

bool Message::setMessageNumber(int number)
{
    this->messageNumber = number;
    return true;
}

bool Message::setSender(string sender)
{
    if (!checkMaxSize(sender, 8) || !isDigitLetterOnly(sender))
        return false;

    this->sender = sender;
    return true;
}

bool Message::setReceiver(string receiver)
{
    if (!checkMaxSize(receiver, 8) || !isDigitLetterOnly(receiver))
        return false;

    this->receiver = receiver;
    return true;
}

bool Message::setSubject(string subject)
{
    if (!checkMaxSize(subject, 80) || !isDigitLetterSpaceOnly(subject))
        return false;

    this->subject = subject;
    return true;
}

bool Message::setMessageContent(string messageContent)
{
    if (!isDigitLetterSpaceOnly(messageContent))
        return false;

    this->messageContent = messageContent;
    return true;
}

void Message::setMessageHead(SendOption messageHead)
{
    switch (messageHead)
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

bool Message::setMessageHead(std::string messageHead)
{
    if(messageHead != "SEND\n" && messageHead != "LIST\n" && messageHead != "READ\n" && messageHead != "DEL\n" && messageHead != "QUIT\n")
        return false;
    this->messageHead = messageHead;
    return true;
}

int Message::getMessageNumber()
{
    return messageNumber;
}
std::string Message::getSender()
{
    return sender;
}
std::string Message::getReceiver()
{
    return receiver;
}
std::string Message::getSubject()
{
    return subject;
}
std::string Message::getMessageContent()
{
    return messageContent;
}

std::vector<std::string> Message::getMessageString()
{
    return messageString;
}

void Message::cleanMsg()
{
    messageHead = "";
    receiver = "";
    subject = "";
    messageContent = "";
    messageNumber = -1;
    messageString.clear();
}

void Message::createMsgString()
{
    messageString.push_back(messageHead);

    if (sender != "")
        messageString.push_back(sender + "\n");

    if (receiver != "")
        messageString.push_back(receiver + "\n");

    if (subject != "")
        messageString.push_back(subject + "\n");

    if (messageContent != "")
        messageString.push_back(messageContent + "\n");

    if (messageNumber != -1)
        messageString.push_back(to_string(messageNumber) + "\n");

    if (messageHead == "SEND\n")
        messageString.push_back(".\n");
}