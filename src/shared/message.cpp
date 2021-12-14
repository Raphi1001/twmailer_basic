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
