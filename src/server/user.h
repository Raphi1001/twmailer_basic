#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>
#include <string.h>

#include "../shared/message.h"

class User
{

private:
    std::string username;
    std::vector<Message> recievedMessages;

public:
    /* SETTER */
    void setUsername(std::string username);
    void addMessage(Message msg);

    /* GETTER */
    std::vector<Message> getMessages();

    /* FUNC */
    void loadUser(std::string username, std::string userDirectory);
};
#endif