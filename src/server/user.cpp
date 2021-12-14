#include "user.h"

using namespace std;

void User::setUsername(std::string username)
{
    this->username = username;
}

void User::addMessage(Message msg)
{
    recievedMessages.push_back(msg);
}

vector<Message> User::getMessages()
{
    return recievedMessages;
}

void User::loadUser(string username, string userDirectory)
{
    setUsername(username);

    struct dirent *direntp;
    DIR *dirp = opendir(userDirectory.c_str());
    if (!dirp)
    {
        cerr << "Directory konnte nicht geöffnet werden: " << userDirectory << endl;
        exit(EXIT_FAILURE);
    }
    while ((direntp = readdir(dirp)) != NULL)
    {

        if (strcmp(direntp->d_name, ".") != 0 && strcmp(direntp->d_name, "..") != 0) //"." und ".." Verzeichnisse überspringen
        {
            string filepath(userDirectory + "/" + direntp->d_name);
            Message newMsg;
            newMsg.loadMessage(filepath);
            addMessage(newMsg);
        }
    }
    closedir(dirp);
}