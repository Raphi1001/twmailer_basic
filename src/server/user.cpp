#include "user.h"

using namespace std;

void User::setUsername(std::string username)
{
    if (!checkMaxSize(username, 8) || !isDigitLetterOnly(username))
        exitFailure("Ungültiger Username: " + username);
    this->username = username;
}

void User::addMessage(Message msg, string pathToMsg)
{
    receivedMessages.push_back(msg);
    fileCount++;

    ofstream newMsg(pathToMsg);
    newMsg << msg.getSender() << endl
           << msg.getReceiver() << endl
           << msg.getSubject() << endl
           << msg.getMessageContent() << endl;

    newMsg.close();
}

vector<Message> User::getMessages()
{
    return receivedMessages;
}

string User::getUsername()
{
    return username;
}

void User::loadUser(string username, string userDirectory)
{
    setUsername(username);

    struct dirent *direntp;
    DIR *dirp = opendir(userDirectory.c_str());
    if (!dirp)
        exitFailure("Directory konnte nicht geöffnet werden: " + userDirectory);

    while ((direntp = readdir(dirp)) != NULL)
    {
        if (strcmp(direntp->d_name, ".") != 0 && strcmp(direntp->d_name, "..") != 0) //"." und ".." Verzeichnisse überspringen
        {
            string filepath(userDirectory + "/" + direntp->d_name);
            Message newMsg;
            newMsg.loadMessage(filepath, fileCount);
            receivedMessages.push_back(newMsg);
            fileCount++;
        }
    }
    closedir(dirp);
}