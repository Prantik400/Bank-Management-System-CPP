#include "helpers.h"
#include <iostream>
#include <ctime>
#include <cctype>

using namespace std;

// ================= INTEGER CHECK =================
bool isInteger(const string& s)
{
    if (s.empty()) return false;

    int start = 0;

    if (s[0] == '-')
    {
        if (s.length() == 1) return false;
        start = 1;
    }

    for (int i = start; i < s.length(); i++)
    {
        if (!isdigit(s[i]))
            return false;
    }

    return true;
}

// ================= NUMBER CHECK =================
bool isNumber(const string& s)
{
    if (s.empty()) return false;

    for (char c : s)
    {
        if (!isdigit(c))
            return false;
    }

    return true;
}

// ================= DOUBLE CHECK =================
bool isDouble(const string& s)
{
    if (s.empty()) return false;

    bool dotSeen = false;
    bool digitSeen = false;

    for (char c : s)
    {
        if (c == '.')
        {
            if (dotSeen) return false;
            dotSeen = true;
        }
        else if (isdigit(c))
        {
            digitSeen = true;
        }
        else
        {
            return false;
        }
    }

    return digitSeen;
}

// ================= NAME VALIDATION =================
bool isValidName(const string& s)
{
    if (s.empty()) return false;

    for (char c : s)
    {
        if (!isalpha(c) && c != ' ')
            return false;
    }

    return true;
}

// ================= CURRENT TIME =================
string getCurrentTime()
{
    time_t now = time(0);
    char* dt = ctime(&now);
    return string(dt);
}

// ================= CLEAR INPUT BUFFER =================
void clearInputBuffer()
{
    cin.clear();
    cin.ignore(10000, '\n');
}

// ================= TRIM FUNCTION =================
string trim(const string& str)
{
    size_t start = 0;
    size_t end = str.length();

    // remove leading spaces
    while (start < end && isspace(str[start]))
        start++;

    // remove trailing spaces
    while (end > start && isspace(str[end - 1]))
        end--;

    return str.substr(start, end - start);
}