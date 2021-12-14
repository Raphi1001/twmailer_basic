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
class Database
{

private:
    std::string dir;
    std::vector<User> users;

public:
    void setDir(std::string dirName);
    bool dirExists();
    bool dirIsEmpty();
    void loadDatabase();
    void addUser(User user);
    void loadUser(std::string userDirectory);
};
#endif