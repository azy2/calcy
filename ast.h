#ifndef AST_H
#define AST_H

#include "token.h"
#include <vector>

using std::vector;

class AST {
public:
    AST() {}
    AST(Token *t) : token(t) {}
    Token *token;
    vector<AST *> children;
};


#endif//AST_H
