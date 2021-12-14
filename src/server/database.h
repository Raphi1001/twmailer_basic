#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <vector>
#include <string>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <string.h>
#include <filesystem>
#include <dirent.h>

#include "user.h"
#include "../shared/functions.h"

class Database
{

private:
    std::string dir;
    std::vector<User> users;

public:
    /* SETTER */

    void setDir(std::string dirName);
    void addUser(User user);

    /* GETTER */

    std::vector<User> getUsers();

    /* FUNC */

    bool dirExists();
    bool dirIsEmpty();
    void loadDatabase();
    void send();
};
#endif