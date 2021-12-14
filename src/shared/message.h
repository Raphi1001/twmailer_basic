#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <iostream>
#include <fstream>

#include "functions.h"

class Message
{
private:
    int messageNumber;
    std::string sender;
    std::string reciever;
    std::string subject;
    std::string messageContent;

public:
    /* SETTER */
    bool setMessageNumber(int messageNumber);
    bool setSender(std::string sender);
    bool setReciever(std::string reciever);
    bool setSubject(std::string subject);
    bool setMessageContent(std::string messageContent);

    /* GETTER */
    int getMessageNumber();
    std::string getSender();
    std::string getReciever();
    std::string getSubject();
    std::string getMessageContent();

    /* FUNC */
    void loadMessage(std::string msgPath);

    Message();
};
#endif