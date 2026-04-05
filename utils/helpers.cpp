#include "helpers.h"
#include <iostream>
#include <ctime>
#include <sstream>
#include <iomanip>
#include <cctype>



using namespace std;

bool isInteger(const string& s) {
   if(s.empty()) return false;

   int start=0;
   if(s[0]=='-')
   {
    if(s.length()==1) return false; // Just a '-' is not an integer
    start=1; // Start checking from the next character
   }

   for(int i=start; i<s.length(); i++) {
       if(!isdigit(s[i])) {
           return false;
       }
   }
   return true;

}

bool isNumber(const string& s) {
    for(char c : s) {
        if(!isdigit(c)) {
            return false;
        }
    }
    return !s.empty();
}

bool isDouble(const string& s) {
    bool dotSeen = false;
    for(char c : s) {
        if(c == '.') {
            if(dotSeen) return false; // More than one dot
            dotSeen = true;
        } else if(!isdigit(c)) {
            return false;
        }
    }
    return !s.empty();

}

bool isValidName(const string& s) {
    for(char c : s) {
        if(!isalpha(c) && c != ' ') {
            return false;
        }
    }
    return !s.empty();
}

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