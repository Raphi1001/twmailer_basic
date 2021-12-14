#include "database.h"

using namespace std;

void Database::setDir(string dirName)
{
    this->dir = dirName;
    if (!dirExists())
    {
        if (mkdir(dir.c_str(), S_IRWXU | S_IRWXG | S_IRWXO) == -1)
        {
            cerr << strerror(errno) << endl;
            exit(EXIT_FAILURE);
        }
    }

    if (!dirIsEmpty())
        loadDatabase();
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

void Database::loadDatabase()
{
    struct dirent *direntp;
    DIR *dirp = opendir(dir.c_str());
    if (!dirp)
    {
        cerr << "Directory konnte nicht geöffnet werden: " << dir << endl;
        exit(EXIT_FAILURE);
    }

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

    vector<Message> messages = users[0].getMessages();
    Message message = messages[0];
    cout << message.getMessageContent() << endl;
}

void Database::addUser(User user)
{
    users.push_back(user);
}
