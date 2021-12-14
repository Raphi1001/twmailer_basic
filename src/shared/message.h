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
    void setMessageNumber(int messageNumber);
    void setSender(std::string sender);
    void setReciever(std::string reciever);
    void setSubject(std::string subject);
    void setMessageContent(std::string messageContent);

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