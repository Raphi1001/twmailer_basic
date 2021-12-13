#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <iostream>

class message
{
private:
    std::string sender;
    std::string reciever;
    std::string subject;
    std::string messageContent;
    int messageNumber;

    bool isDigitLetterOnly(std::string word);
    bool checkUser(std::string user);

public:
    bool setSender(std::string sender);
    bool setReciever(std::string reciever);
    bool setSubject(std::string subject);
    bool setMessageContent(std::string messageContent);

    message();
    ~message();
};
#endif