#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include "token.h"
#include "ast.h"

using namespace std;

vector<string> words(string s) {
    vector<string> words;
    size_t a = 0;
    for (size_t b = 0; b < s.length(); b++) {
        if (s.at(b) == ' ' || s.at(b) == '\n') {
            words.push_back(s.substr(a, b - a));
            a = (b+1);
        }
    }
    words.push_back(s.substr(a, s.length() - a));

    return words;
}

AST *createAst(string line) {
    regex identifier("[a-zA-Z\\+-/\\*%@\\$#&!^|]+[a-zA-Z0-9\\+-/\\*%@\\$#&!^|]*");
    regex number("[1-9]+.[0-9]*");
    int i = 0;
    AST *ast = new AST();
    while (line.at(i) != ' ') i++;
    string atom = line.substr(0, i);
    if (regex_match(atom, identifier)) {
        ast->token = (Token *)new TkId(atom);
    } else {
        //TODO first token isn't an identifier wth man
    }
    for (size_t j = i+1; j < line.length(); j++) {
        if (line.at(j) == '(') {
            int a = j;
            while (line.at(a) != ')') a++;
            ast->children.push_back(createAst(line.substr(j+1, (a - j - 2))));
        } else {
            int a = j;
            while (line.at(a) != ' ') a++;
            string atom = line.substr(j, (a - j));
            if (regex_match(atom, identifier)) {
                ast->children.push_back(new AST((Token *)new TkId(atom)));
            }
            if (regex_match(atom, number)) {
                int x = stoi(atom, nullptr, 10);
                ast->children.push_back(new AST((Token *)new TkNum(x)));
            }
            j++;
        }
    }

    return ast;
}

void parse(string line) {
    if (line.at(0) == '(' && line.at(line.length() - 1) == ')') {
        line.erase(0); line.pop_back();
        cout << line << endl;
        AST *ast = createAst(line);
    } else {
        // TODO Not valid syntax yell at user
    }
}

int main() {

    while (true) {
        string line;
        getline(cin, line);
        parse(line);
    }

    return 0;
}
