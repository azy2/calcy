#ifndef TOKEN_H
#define TOKEN_H

#include <string>

using std::string;

class Token {
public:
    virtual string toString() = 0;
};

class TkNum : public Token {
public:
    explicit TkNum(int v) : value(v) {}
    string toString() {return std::to_string(value);}
    int value;
};

class TkId : public Token {
public:
    explicit TkId(string i) : id(i) {}
    string toString() {return id;}
    string id;
};

#endif//TOKEN_H
