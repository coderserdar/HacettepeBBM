#ifndef INCLUDE_STRINGTOKENIZER_H
#define INCLUDE_STRINGTOKENIZER_H


#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string>


class StringTokenizer
{

   public:

    StringTokenizer(const std::string& _str, const std::string& _delim);
   ~StringTokenizer(){};

    int         countTokens();
    bool        hasMoreTokens();
    std::string nextToken();
    int         nextIntToken();
    double      nextFloatToken();
    std::string nextToken(const std::string& delim);
    std::string remainingString();
    std::string filterNextToken(const std::string& filterStr);

   private:

    std::string  token_str;
    std::string  delim;

};

#endif
