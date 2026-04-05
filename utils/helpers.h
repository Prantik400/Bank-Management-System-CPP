#ifndef HELPERS_H
#define HELPERS_H

#include <string>
using namespace std;

string getCurrentTime();
void clearInputBuffer();

bool isInteger(const string& s);
bool isDouble(const string& s);
bool isNumber(const string& s);
bool isValidName(const string& s);

#endif