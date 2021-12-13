#include "message.h"

using namespace std;

message::message()
{
    messageNumber = 1; // ToDO: set messageNumber correctly
}

bool message::setSender(string sender)
{
    if (!checkUser(sender))
        return false;

    this->sender = sender;
    return true;
}

bool message::setReciever(string reciever)
{
    if (!checkUser(reciever))
        return false;

    this->reciever = reciever;
    return true;
}

bool message::setSubject(string subject)
{
    if (subject.length() > 80 || !isDigitLetterOnly(subject))
        return false;

    this->subject = subject;
    return true;
}

bool message::setMessageContent(string messageContent)
{
    if (!isDigitLetterOnly(messageContent))
        return false;
    this->messageContent = messageContent;
    return true;
}

bool message::checkUser(string user)
{
    if (user.length() > 8 || !isDigitLetterOnly(user))
        return false;

    return true;
}

bool message::isDigitLetterOnly(string word)
{
    for (int i = 0; i < (int)word.size(); i++)
    {
        if (!isdigit(word.at(i)) && !isalpha(word.at(i)))
            return false;
    }
    return true;
}
