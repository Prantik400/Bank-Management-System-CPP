#ifndef HELPERS_H
#define HELPERS_H
#include <string>

std::string getCurrentTime();
void clearInputBuffer();

bool isInteger(const std::string& s);
bool isDouble(const std::string& s);
bool isNumber(const std::string& s);
bool isValidName(const std::string& s);

std::string trim(const std::string& str);

#endif