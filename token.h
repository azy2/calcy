#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using std::string;

class Token {
};

class TkNum : Token {
public:
    explicit TkNum(int v) : value(v) {}
    int value;
};

class TkId : Token {
public:
    explicit TkId(string i) : id(i) {}
    string id;
};

#endif//TOKEN_H
