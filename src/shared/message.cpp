#include "message.h"

using namespace std;

Message::Message()
{
}

bool Message::setMessageNumber(int messageNumber)
{
    // TODO: set messageNumber correctly

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
    if (!setReciever(currentLine))
        exitFailure("Ungültiger Empfänger: " + reciever);

    getline(input_file, currentLine);
    if (!setSubject(currentLine))
        exitFailure("Ungültiger Betreff: " + currentLine);

    getline(input_file, currentLine);
    if (!setMessageContent(currentLine))
        exitFailure("Ungültige Nachricht: " + messageContent);

    input_file.close();
}
