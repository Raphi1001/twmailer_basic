#include "message.h"

using namespace std;

Message::Message()
{
}

void Message::setMessageNumber(int messageNumber)
{
    // TODO: set messageNumber correctly

    this->messageNumber = messageNumber;

    return;

    exitFailure("Ungültige MessageNumber: " + messageNumber);
}

void Message::setSender(string sender)
{
    if (!checkMaxSize(sender, 8) || !isDigitLetterOnly(sender))
        exitFailure("Ungültiger Sender: " + sender);

    this->sender = sender;
}

void Message::setReciever(string reciever)
{
    if (!checkMaxSize(reciever, 8) || !isDigitLetterOnly(reciever))
        exitFailure("Ungültiger Empfänger: " + reciever);

    this->reciever = reciever;
}

void Message::setSubject(string subject)
{
    if (!checkMaxSize(subject, 80) || !isDigitLetterOnly(subject))
        exitFailure("Ungültiger Betreff: " + subject);

    this->subject = subject;
}

void Message::setMessageContent(string messageContent)
{
    if (!isDigitLetterOnly(messageContent))
        exitFailure("Ungültige Nachricht: " + messageContent);

    this->messageContent = messageContent;
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
    setMessageNumber(number);

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
