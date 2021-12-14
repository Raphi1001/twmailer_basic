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

int Message::getMessageNumber()
{
    return messageNumber;
}
std::string Message::getSender()
{
    return sender;
}
std::string Message::getreceiver()
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
