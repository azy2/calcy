#include <iostream>
#include <string>
#include <vector>
#include <regex>
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
    regex number("[1-9]+");
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
        if (regex_match(tokens.at(i), identifier)) {
            ast->children.emplace_back(new AST(new TkId(tokens.at(i))));
        }
        if (regex_match(tokens.at(i), number)) {
            int x = stoi(tokens.at(i), nullptr, 10);
            ast->children.emplace_back(new AST(new TkNum(x)));
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

void printAst(AST *ast) {
    cout << ast->token->toString() << endl;
    for (size_t i = 0; i < ast->children.size(); i++) {
        printAst(ast->children.at(i).get());
    }
}

int main() {

    while (true) {
        string line;
        getline(cin, line);
        unique_ptr<AST> ast(parse(line));
        printAst(ast.get());
    }

    return 0;
}
