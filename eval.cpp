
#include "eval.h"

using namespace std;

static map<string,int (*)(vector<int>)> functions;

static int calcyAdd(vector<int> args) {
    int sum = 0;
    for (size_t i = 0; i < args.size(); i++)
        sum += args.at(i);
    return sum;
}

static int calcySub(vector<int> args) {
    int diff = 1;
    for (size_t i = 0; i < args.size(); i++)
        diff -= args.at(i);
    return diff;
}

static int calcyMult(vector<int> args) {
    int prod = 1;
    for (size_t i = 0; i < args.size(); i++)
        prod *= args.at(i);
    return prod;
}

static int calcyDiv(vector<int> args) {
    int quot = args.at(0);
    for (size_t i = 1; i < args.size(); i++)
        quot /= args.at(i);
    return quot;
}

static int calcyMod(vector<int> args) {
    return args.at(0) % args.at(1);
}

void initializeBuiltins() {
    functions["+"] = calcyAdd;
    functions["-"] = calcySub;
    functions["*"] = calcyMult;
    functions["/"] = calcyDiv;
    functions["%"] = calcyMod;
}

int eval(AST *ast) {
    if (TkNum *t = dynamic_cast<TkNum*>(ast->token.get()))
        return t->value;
    vector<int> args;
    for (size_t i = 0; i < ast->children.size(); i++)
        args.push_back(eval(ast->children.at(i).get()));
    int result = (*functions[ast->token->toString()])(args);
    return result;
}
