#include <assert.h>
#include <iostream>

#include "tokenizer.hpp"

namespace lexer {

    vector<Token> Lexer::runLexer(const string& source) {
        Token currTok;
        vector<Token> tokens;

        for (char c : source) {
            switch(c) {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    if (currTok.mType == WHITESPACE) {
                        currTok.mType = NUMBER_LITERAL;
                        currTok.mLexeme.push_back(c);
                    } else {
                        currTok.mLexeme.push_back(c);
                    }
                    break;
                
                case '+':
                case '-':
                case '*':
                case '=':
                    if (currTok.mType == WHITESPACE) {
                        endToken(currTok, tokens);
                        currTok.mType = OPERATOR;
                        currTok.mLexeme.push_back(c);
                        endToken(currTok, tokens);
                    } else {
                        currTok.mLexeme.push_back(c);
                    }
                    break;

                case '/':
                    break;

                case ' ':
                case '\t':
                case '\r':
                case '\n':
                    if (currTok.mType == STRING_LITERAL) {
                        currTok.mLexeme.push_back(c);
                    } else {
                        endToken(currTok, tokens);
                        break;
                    }

                case '"':
                    if (currTok.mType == WHITESPACE) {
                        currTok.mType = STRING_LITERAL;
                    } else {
                        endToken(currTok, tokens);
                    }
                    break;

                case '.':
                    if (currTok.mType == NUMBER_LITERAL) {
                        currTok.mType = FLOAT_LITERAL;
                        currTok.mLexeme.push_back(c);
                    } else {
                        currTok.mLexeme.push_back(c);
                    }
                    break;
                
                case '{':
                case '}':
                case '(':
                case ')':
                case ':':
                    if (currTok.mType == STRING_LITERAL) {
                        currTok.mLexeme.push_back(c);
                    } else {
                        endToken(currTok, tokens);
                        currTok.mType = PUNCTUATOR;
                        currTok.mLexeme.push_back(c);
                        endToken(currTok, tokens);
                    }
                    break;
                
                default:
                    if (currTok.mType == WHITESPACE) {
                        currTok.mType = IDENTIFIER;
                        currTok.mLexeme.push_back(c);
                    } else {
                        currTok.mLexeme.push_back(c);
                    }
                    break;
            }
            // cout << c << sTokenTypeStrings[currTok.mType] << endl;
        }
        endToken(currTok, tokens);
        return tokens;
    }

    void Lexer::endToken(Token& currTok, vector<Token>& tokens) {
        if (currTok.mType == WHITESPACE) {
            currTok.mLexeme.erase();
            return;
        } 
         
        if (currTok.mType == NUMBER_LITERAL) {
            currTok.mType = INTEGER_LITERAL;
        } 

        tokens.push_back(currTok);
        currTok.mLexeme.erase();
        currTok.mType = WHITESPACE;
    }

    void Token::debugPrint() {
        cout << "(TYPE: " << sTokenTypeStrings[mType] << ", VALUE: " << mLexeme << ")" << endl;
    }
}