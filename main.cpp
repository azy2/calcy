#include <iostream>
#include "token.h"
#include "ast.h"
#include "parser.h"
#include "eval.h"

using namespace std;

int main() {
    initializeBuiltins();
    while (true) {
        string line;
        getline(cin, line);
        unique_ptr<AST> ast(parse(line));
        int res = eval(ast.get());
        cout << res << endl;
    }

    return 0;
}
