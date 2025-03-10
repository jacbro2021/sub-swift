#include <iostream>
#include <vector>
#include <string>

#include "tokenizer.hpp"

using namespace std;
using namespace lexer;

int main() {
    cout << "Sub-Swift 0.0.1\n" << endl;

    string sandbox_test = "/Users/jsbrown/Developer/sub-swift/tests/sandbox.swift";
    string var_test = "/Users/jsbrown/Developer/sub-swift/tests/var.swift";
    string basic_func_test = "/Users/jsbrown/Developer/sub-swift/tests/basic_func.swift";

    FILE * fh = fopen(sandbox_test.data(), "r");
    if (!fh) {
        cerr << "Can't find file" << endl;
    }

    fseek(fh, 0, SEEK_END);
    size_t fileSize = ftell(fh);
    fseek(fh, 0, SEEK_SET);
    string file_contents(fileSize, ' ');
    fread(file_contents.data(), 1, fileSize, fh);

    cout << "TEST INPUT:\n\n" << file_contents << "\n" << endl;

    cout << "TEST OUTPUT:\n" << endl;
    Lexer lex = Lexer();
    vector<Token> toks = lex.runLexer(file_contents);
    for (auto tok : toks) {
        tok.debugPrint();
    }

    return 0;
}