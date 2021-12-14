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
    std::string receiver;
    std::string subject;
    std::string messageContent;

public:
    /* SETTER */
    bool setMessageNumber(int number);
    bool setSender(std::string sender);
    bool setReceiver(std::string receiver);
    bool setSubject(std::string subject);
    bool setMessageContent(std::string messageContent);

    /* GETTER */
    int getMessageNumber();
    std::string getSender();
    std::string getReceiver();
    std::string getSubject();
    std::string getMessageContent();

    /* FUNC */
    void loadMessage(std::string msgPath, int number);

    Message();
};
#endif