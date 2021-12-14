#ifndef USER_H
#define USER_H

#include <iostream>
#include <string>
#include <vector>
#include <dirent.h>
#include <string.h>

#include "../shared/message.h"
#include "../shared/functions.h"

class User
{

private:
    std::string username;
    std::vector<Message> receivedMessages;
    int fileCount = 0;

public:
    /* SETTER */
    void setUsername(std::string username);
    void addMessage(Message msg, std::string pathToMsg);

    /* GETTER */
    std::vector<Message> getMessages();
    std::string getUsername();

    /* FUNC */
    void loadUser(std::string username, std::string userDirectory);
};
#endif