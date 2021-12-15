#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>
#include <iostream>

void exitFailure(std::string errorMsg);
bool checkMaxSize(std::string word, int max);
bool isDigitLetterOnly(std::string word);
bool isDigitLetterSpaceOnly(std::string word);

#endif