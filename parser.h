#include <vector>
#include <string>
#include <regex>
#include <iostream>
#include <sstream>
#include "token.h"
#include "ast.h"

using namespace std;

vector<string> tokenize(string s) {
    vector<string> tokens;
    if (s.at(0) != '(' || s.at(s.size() - 1) != ')')
        cout << "tokenize received a improperly formatted string" << endl;
    size_t i = 1;
    while (i < s.size() - 1) {
        while (s.at(i) == ' ')
            i++;
        if (s.at(i) == '(') {
            size_t j = i;
            int pcount = 1;
            while (pcount > 0) {
                i++;
                if (s.at(i) == '(')
                    pcount++;
                if (s.at(i) == ')')
                    pcount--;
            }
            i++;
            tokens.push_back(s.substr(j, (i - j)));
        }
        else {
            size_t j = i;
            while (j < s.size() && s.at(j) != ' ' && s.at(j) != '(' && s.at(j) != ')')
                j++;
            tokens.push_back(s.substr(i, (j-i)));
            i = j;
        }
    }
    return tokens;
}

AST *createAst(vector<string> tokens) {
    regex identifier("[a-zA-Z\\+-/\\*%@\\$#&!^|]+[a-zA-Z0-9\\+-/\\*%@\\$#&!^|]*");
    regex number("((\\+|-)?[[:digit:]]+)(\\.(([[:digit:]]+)?))?((e|E)((\\+|-)?)[[:digit:]]+)?");
    AST *ast = new AST();
    if (regex_match(tokens.at(0), identifier)) {
        ast->token = unique_ptr<Token>(new TkId(tokens.at(0)));
    }
    if (regex_match(tokens.at(0), number)) {
        int x = stoi(tokens.at(0), nullptr, 10);
        ast->token = unique_ptr<Token>(new TkNum(x));
    }
    size_t i = 1;
    while (i < tokens.size()) {
        if (tokens.at(i).at(0) == '(')
            ast->children.emplace_back(createAst(tokenize(tokens.at(i))));
        else if (regex_match(tokens.at(i), number)) {
            int x = 0;
            stringstream(tokens.at(i)) >> x;
            ast->children.emplace_back(new AST(new TkNum(x)));
        }
        else if (regex_match(tokens.at(i), identifier)) {
            ast->children.emplace_back(new AST(new TkId(tokens.at(i))));
        }
        i++;
    }

    return ast;
}

AST* parse(string line) {
    auto tokens = tokenize(line);

    AST *ast = createAst(tokens);

    return ast;
}
