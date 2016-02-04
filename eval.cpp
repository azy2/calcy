
#include "eval.h"
#include <iostream>
#include <cmath>

using namespace std;

static map<string,Type* (*)(vector<Type *>)> functions;

static Type *calcyAdd(vector<Type *> args) {
    bool doubles = false;
    for (size_t i = 0; i < args.size(); i++) {
        if (args.at(i)->type != CALCY_INT && args.at(i)->type != CALCY_DOUBLE) {
            cout << "Incorrect argument type given to +" << endl;
            return new TypeNothing();
        }
        if (args.at(i)->type == CALCY_DOUBLE)
            doubles = true;
    }
    if (doubles) {
        double sum = 0;
        for (auto i = args.begin(); i != args.end(); i++) {
            if ((*i)->type == CALCY_INT) {
                TypeInt *n = dynamic_cast<TypeInt *>(*i);
                sum += n->value;
            }
            if ((*i)->type == CALCY_DOUBLE) {
                TypeDouble *n = dynamic_cast<TypeDouble *>(*i);
                sum += n->value;
            }
        }
        return new TypeDouble(sum);
    } else {
        int sum = 0;
        for (auto i = args.begin(); i != args.end(); i++) {
            TypeInt *n = dynamic_cast<TypeInt *>(*i);
            sum += n->value;
        }
        return new TypeInt(sum);
    }
}

// static Type calcySub(vector<Type> args) {
//     int diff = 1;
//     for (size_t i = 0; i < args.size(); i++)
//         diff -= args.at(i);
//     return diff;
// }

// static Type calcyMult(vector<Type> args) {
//     int prod = 1;
//     for (size_t i = 0; i < args.size(); i++)
//         prod *= args.at(i);
//     return prod;
// }

// static Type calcyDiv(vector<Type> args) {
//     int quot = args.at(0);
//     for (size_t i = 1; i < args.size(); i++)
//         quot /= args.at(i);
//     return quot;
// }

// static Type calcyMod(vector<Type> args) {
//     return args.at(0) % args.at(1);
// }

// static Type calcyExp(vector<Type> args) {
//     return pow(args.at(0), args.at(1));
// }

void initializeBuiltins() {
    functions["+"] = calcyAdd;
    // functions["-"] = calcySub;
    // functions["*"] = calcyMult;
    // functions["/"] = calcyDiv;
    // functions["%"] = calcyMod;
    // functions["^"] = calcyExp;
}

Type *eval(AST *ast) {
    if (ast->token.get()->type != CALCY_ID) {
        return ast->token.get();
    }

    vector<Type *> args;
    for (size_t i = 0; i < ast->children.size(); i++)
        args.emplace_back(eval(ast->children.at(i).get()));
    Type *result = (*functions[ast->token->toString()])(args);
    return result;
}
