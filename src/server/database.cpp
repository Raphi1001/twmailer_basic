#include "database.h"

using namespace std;

void Database::setDir(string dirName)
{
    this->dir = dirName;
    if (!dirExists())
    {
        if (mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IRWXO) == -1)
            exitFailure((char *)errno);
    }

    if (!dirIsEmpty())
        loadDatabase();
}

void Database::addUser(User user)
{
    for (int i = 0; i < (int)users.size(); i++)
    {
        if (user.getUsername() == users[i].getUsername())
            exitFailure("Duplicate User: " + user.getUsername());
    }

    users.push_back(user);
}

vector<User> Database::getUsers()
{
    return users;
}

bool Database::dirExists()
{
    struct stat st = {0};

    if (stat(dir.c_str(), &st) == -1)
        return false;

    return true;
}

bool Database::dirIsEmpty()
{
    const filesystem::path dirPath{dir};
    if (filesystem::is_empty(dirPath))
        return true;

    return false;
}

// laed existierende datenbank
void Database::loadDatabase()
{
    struct dirent *direntp;
    DIR *dirp = opendir(dir.c_str());
    if (!dirp)
        exitFailure("Directory konnte nicht geöffnet werden: " + dir);

    while ((direntp = readdir(dirp)) != NULL)
    {

        if (strcmp(direntp->d_name, ".") != 0 && strcmp(direntp->d_name, "..") != 0) //"." und ".." Verzeichnisse überspringen
        {
            string currentUserPath(dir + "/" + direntp->d_name);
            User newUser;
            newUser.loadUser(direntp->d_name, currentUserPath);
            addUser(newUser);
        }
    }
    closedir(dirp);
}
