#include "functions.h"

using namespace std;

// gibt Fehlermeldung aus und beendet das Programm
void exitFailure(string errorMsg)
{
    std::cerr << errorMsg << std::endl;
    exit(EXIT_FAILURE);
}

// prüft ob ein string eine gegebene Maximallänge nicht überschreitet
bool checkMaxSize(string str, int max)
{
    if ((int)str.size() > max)
        return false;

    return true;
}

// prüft ob ein string nur aus buchstaben und zahlen besteht
bool isDigitLetterOnly(string str)
{
    for (int i = 0; i < (int)str.size(); i++)
    {
        if (!isdigit(str.at(i)) && !isalpha(str.at(i)))
            return false;
    }
    return true;
}
