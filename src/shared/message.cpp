#include "message.h"

using namespace std;

Message::Message()
{
}

bool Message::setMessageNumber(int number)
{
    Message::messageCount++;
    this->messageNumber = messageCount;
    return true;
}

bool Message::setSender(string sender)
{
    if (!checkMaxSize(sender, 8) || !isDigitLetterOnly(sender))
        return false;

    this->sender = sender;
    return true;
}

bool Message::setreceiver(string receiver)
{
    if (!checkMaxSize(receiver, 8) || !isDigitLetterOnly(receiver))
        return false;

    this->receiver = receiver;
    return true;
}

bool Message::setSubject(string subject)
{
    if (!checkMaxSize(subject, 80) || !isDigitLetterOnly(subject))
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
        exitFailure("File konnte nicht geöffnet werden: " + msgPath);

    string currentLine;

    getline(input_file, currentLine);
    char *end;
    int number = strtol(currentLine.c_str(), &end, 10);
    if (!setMessageNumber(number))
        exitFailure("Ungültige MessageNumber: " + messageNumber);

    getline(input_file, currentLine);
    if (!setSender(currentLine))
        exitFailure("Ungültiger Sender: " + sender);

    getline(input_file, currentLine);
    if (!setreceiver(currentLine))
        exitFailure("Ungültiger Empfänger: " + receiver);

    getline(input_file, currentLine);
    if (!setSubject(currentLine))
        exitFailure("Ungültiger Betreff: " + currentLine);

    getline(input_file, currentLine);
    if (!setMessageContent(currentLine))
        exitFailure("Ungültige Nachricht: " + messageContent);

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
