#ifndef CLIENT_H
#define CLIENT_H

#include <string>

class message
{
private:
    std::string sender;
    std::string reciever;
    std::string subject;
    std::string messageContent;

public:
    bool message::setSender(std::string sender);
    bool message::setReciever(std::string sender);

    bool message::setUser(std::string sender);
};
#endif