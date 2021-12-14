#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <iostream>

namespace generalFuncions
{
    bool exitFailure(std::string errorMsg);
    bool checkMaxSize(std::string word, int max);
    bool isDigitLetterOnly(std::string word);
} // namespace generalFunctions

#endif