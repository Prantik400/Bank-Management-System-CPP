#include "helpers.h"
#include <ctime>
#include <iostream>
using namespace std;


string getCurrentTime()
{
    time_t now = time(0);
    char* dt = ctime(&now);
    return string(dt);
}

void clearInputBuffer()
{
    cin.clear();
    cin.ignore(10000, '\n');
}