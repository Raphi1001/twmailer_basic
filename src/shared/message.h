#ifndef MESSAGE_H
#define MESSAGE_H

#include <string>
#include <iostream>
#include "SendOptionEnum.h"

#include <fstream>

class Message
{
private:
    int messageNumber;
    std::string sender;
    std::string reciever;
    std::string subject;
    std::string messageContent;
    std::string messageHead;
    std::string messageString;

public:
    /* SETTER */
    bool setMessageNumber(int messageNumber);
    bool setSender(std::string sender);
    bool setReciever(std::string reciever);
    bool setSubject(std::string subject);
    bool setMessageContent(std::string messageContent);
    void setMessageHead(SendOption messageHead);

    /* GETTER */
    int getMessageNumber();
    std::string getSender();
    std::string getReciever();
    std::string getSubject();
    std::string getMessageContent();
    std::string getMessageHead();
    std::string getMessageString();

    /* FUNC */
    void loadMessage(std::string msgPath);
    void cleanMsg();
    void createMsgString();

    Message();
};
#endif