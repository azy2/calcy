#ifndef AST_H
#define AST_H

#include "token.h"
#include <vector>
#include <memory>

using std::vector;

class AST {
public:
    AST() {}
    AST(Token *t) : token(t) {}
    std::unique_ptr<Token> token;
    vector<std::unique_ptr<AST>> children;
};


#endif//AST_H
