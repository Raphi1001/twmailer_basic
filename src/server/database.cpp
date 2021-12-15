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
        {
            exitFailure("Duplicate User: " + user.getUsername());
        }
    }

    users.push_back(user);
}

bool Database::addNewUser(User *newUser, std::string username)
{
    // username hinzufügen
    if (!newUser->setUsername(username))
        return false;

    // user directory hinzufügen
    string path = dir + "/" + username;
    if (mkdir(path.c_str(), S_IRWXU | S_IRWXG | S_IRWXO) == -1)
    {
        exitFailure((char *)errno);
        return false;
    }

    return true;
}

vector<User> Database::getAllUsers()
{
    return users;
}

User *Database::getUser(string username)
{
    for (int i = 0; i < (int)users.size(); ++i)
    {
        if (username == users[i].getUsername())
        {
            return &users[i];
        }
    }
    return nullptr;
}

Message *Database::getUserMessage(string username, int msgNumber)
{
    User *foundUser = getUser(username);

    if (foundUser == nullptr)
        return nullptr;

    Message *foundMessage = foundUser->getMessage(msgNumber);
    if (foundMessage == nullptr)
        return nullptr;

    return foundMessage;
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
        exitFailure("Ungültige Datenbank. Directory konnte nicht geöffnet werden: " + dir);

    while ((direntp = readdir(dirp)) != NULL)
    {
        if (strcmp(direntp->d_name, ".") != 0 && strcmp(direntp->d_name, "..") != 0) //"." und ".." Verzeichnisse überspringen
            loadUser(direntp->d_name);
    }
    closedir(dirp);
}

void Database::loadUser(string username)
{
    User newUser;
    newUser.setUsername(username);

    struct dirent *direntp;
    string userDirectory(dir + "/" + username);
    DIR *dirp = opendir(userDirectory.c_str());
    if (!dirp)
        exitFailure("Ungültige Datenbank. Directory konnte nicht geöffnet werden: " + userDirectory);

    while ((direntp = readdir(dirp)) != NULL)
    {
        if (strcmp(direntp->d_name, ".") != 0 && strcmp(direntp->d_name, "..") != 0) //"." und ".." Verzeichnisse überspringen
        {
            string filepath(userDirectory + "/" + direntp->d_name);
            newUser.loadMessage(filepath);
        }
    }
    closedir(dirp);
    addUser(newUser);
}

bool Database::sendMessage(string sender, string receiver, string subject, string messageContent)
{
    User newUser;
    User *existingUser = getUser(receiver);
    User *user = existingUser;

    if (!existingUser)
    {
        addNewUser(&newUser, receiver);
        user = &newUser;
    }

    if (!user)
        return false; // ungültiger user

    if (!addMessageToUser(user, sender, receiver, subject, messageContent))
        return false;

    if (!existingUser)
        addUser(newUser);

    return true;
}

User *Database::sendMessageToExistingUser(string username)
{
    // add message to existing user
    for (int i = 0; i < (int)users.size(); i++)
    {
        if (username == users[i].getUsername())
        {

            return &users[i];
        }
    }
    return nullptr;
}

bool Database::addMessageToUser(User *user, string sender, string receiver, string subject, string messageContent)
{
    string newPath(dir + "/" + user->getUsername() + "/" + getCurrentTime() + ".txt");
    if (!user->addMessage(sender, receiver, subject, messageContent, newPath))
        return false;

    return true;
}

bool Database::deleteUserMessage(string username, int msgNumber)
{
    User *foundUser = getUser(username);

    if (foundUser == nullptr)
        return false;

    string userDirectory(dir + "/" + foundUser->getUsername());
    if (!foundUser->deleteMessage(msgNumber, userDirectory))
        return false;

    return true;
}

void Database::printAllUsers()
{
    for (int i = 0; i < (int)users.size(); ++i)
    {
        cout << "USERNAME: " << users[i].getUsername() << endl;
        vector<Message> test;
        test = users[i].getAllMessages();
        for (int i = 0; i < (int)test.size(); ++i)
        {
            cout << "   message: " << test[i].getSubject() << endl;
        }
    }
}
