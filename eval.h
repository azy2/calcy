#ifndef EVAL_H
#define EVAL_H

#include <map>
#include <string>
#include <vector>
#include <memory>
#include "ast.h"
#include "token.h"

using namespace std;

void initializeBuiltins();

int eval(AST *ast);

#endif
