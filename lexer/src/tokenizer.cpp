#include <iostream>
#include <stdexcept>

#include "tokenizer.hpp"

namespace lexer {
    Lexer::Lexer() {
        mKeywords["let"] = Keyword("let", LET);
        mKeywords["var"] = Keyword("var", VAR);
        mKeywords["func"] = Keyword("func", FUNC);
        mKeywords["return"] = Keyword("return", RETURN);
        mKeywords["if"] = Keyword("if", IF);
        mKeywords["else"] = Keyword("else", ELSE);
        mKeywords["true"] = Keyword("true", TRUE);
        mKeywords["false"] = Keyword("false", FALSE);

        mTypes["Int"] = Type("Int", INT);
        mTypes["Double"] = Type("Double", DOUBLE);
        mTypes["String"] = Type("String", STRING);
        mTypes["Bool"] = Type("Bool", BOOL);
    }

    vector<Token> Lexer::runLexer(const string& source) {
        Token currTok;
        vector<Token> tokens;
        int column = 1;
        int row = 1;

        for (char c : source) {
            if (currTok.mType == POTENTIAL_COMMENT) {
                if (c == '/') {
                    currTok.mType = COMMENT;
                    currTok.mLexeme.push_back(c);
                    ++mColumn;
                    continue;
                } else {
                    currTok.mType = OPERATOR;
                    endToken(currTok, tokens);
                }
            } else if (currTok.mType == POTENTIAL_EXTENDED_OPERATOR) {
                if (c == '=') {
                    currTok.mType = OPERATOR;
                    currTok.mLexeme.push_back(c);
                    endToken(currTok, tokens);
                    ++mColumn;
                    continue;
                } else {
                    currTok.mType = OPERATOR;
                    endToken(currTok, tokens);
                }
            } else if (currTok.mType == POTENTIAL_ARROW) {
                if (c == '>') {
                    currTok.mType = PUNCTUATOR;
                    currTok.mLexeme.push_back(c);
                    endToken(currTok, tokens);
                    ++mColumn;
                    continue;
                } else {
                    currTok.mType = OPERATOR;
                    endToken(currTok, tokens);
                }
            }

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
                        currTok.mColumn = mColumn;
                        currTok.mType = NUMBER_LITERAL;
                        currTok.mLexeme.push_back(c);
                    } else {
                        currTok.mLexeme.push_back(c);
                    }
                    break;
               
                case '-':
                    if (currTok.mType == STRING_LITERAL || currTok.mType == COMMENT) {
                        currTok.mLexeme.push_back(c);
                    } else {
                        endToken(currTok, tokens);
                        currTok.mColumn = mColumn;
                        currTok.mType = POTENTIAL_ARROW;
                        currTok.mLexeme.push_back(c);
                    }
                    break;

                case '+':
                case '*':
                    if (currTok.mType == STRING_LITERAL || currTok.mType == COMMENT) {
                        currTok.mLexeme.push_back(c);
                    } else {
                        endToken(currTok, tokens);
                        currTok.mColumn = mColumn;
                        currTok.mType = OPERATOR;
                        currTok.mLexeme.push_back(c);
                        endToken(currTok, tokens);
                    }
                    break;

                case '>':
                case '<':
                case '=':
                    if (currTok.mType == STRING_LITERAL || currTok.mType == COMMENT) {
                        currTok.mLexeme.push_back(c);
                    }else {
                        endToken(currTok, tokens);
                        currTok.mType = POTENTIAL_EXTENDED_OPERATOR;
                        currTok.mColumn = mColumn;
                        currTok.mLexeme.push_back(c);
                    }
                    break;

                case '/':
                    if (currTok.mType == STRING_LITERAL) {
                        currTok.mLexeme.push_back(c);
                    } else {
                        endToken(currTok, tokens);
                        currTok.mType = POTENTIAL_COMMENT;
                        currTok.mColumn = mColumn;
                        currTok.mLexeme.push_back(c);
                    }
                    break;

                case ' ':
                case '\t':
                    if (currTok.mType == COMMENT) {
                        currTok.mLexeme.push_back(c);
                    } else if (currTok.mType == STRING_LITERAL) {
                        currTok.mLexeme.push_back(c);
                    } else {
                        endToken(currTok, tokens);
                    }
                    break;

                case '\r':
                case '\n':
                    if (currTok.mType == STRING_LITERAL) {
                        currTok.mLexeme.push_back(c);
                    } else {
                        endToken(currTok, tokens);
                        ++mLine;
                        mColumn = 0;
                    }
                    break;

                case '"':
                    if (currTok.mType == WHITESPACE) {
                        currTok.mColumn = mColumn;
                        currTok.mType = STRING_LITERAL;
                    } else {
                        endToken(currTok, tokens);
                    }
                    break;

                case '.':
                    if (currTok.mType == NUMBER_LITERAL) {
                        currTok.mType = FLOAT_LITERAL;
                        currTok.mLexeme.push_back(c);
                    } else if (currTok.mType == FLOAT_LITERAL) {
                        throw runtime_error("Error: Unexpected \".\" found.");
                    }else {
                        currTok.mLexeme.push_back(c);
                    }
                    break;
                
                case '{':
                case '}':
                case '(':
                case ')':
                case ',':
                case ':':
                    if (currTok.mType == STRING_LITERAL) {
                        currTok.mLexeme.push_back(c);
                    } else {
                        endToken(currTok, tokens);
                        currTok.mColumn = mColumn;
                        currTok.mType = PUNCTUATOR;
                        currTok.mLexeme.push_back(c);
                        endToken(currTok, tokens);
                    }
                    break;
                
                default:
                    if (currTok.mType == WHITESPACE) {
                        currTok.mColumn = mColumn;
                        currTok.mType = IDENTIFIER;
                        currTok.mLexeme.push_back(c);
                    } else {
                        currTok.mLexeme.push_back(c);
                    }
                    break;
            }
            ++mColumn;
        }
        endToken(currTok, tokens);
        return tokens;
    }

    void Lexer::endToken(Token& currTok, vector<Token>& tokens) {
        if (currTok.mType == WHITESPACE || currTok.mType == COMMENT) {
            currTok.mType = WHITESPACE;
            currTok.mLexeme.erase();
            return;
        } 
         
        if (currTok.mType == NUMBER_LITERAL) {
            currTok.mType = INTEGER_LITERAL;
        } else if (currTok.mType == IDENTIFIER) {
            if (checkKeyword(currTok)) {
                currTok.mType = KEYWORD;
            } else if (checkType(currTok)) {
                currTok.mType = TYPE;
            }
        }

        currTok.mLine = mLine;
        tokens.push_back(currTok);

        currTok.mLexeme.erase();
        currTok.mType = WHITESPACE;
        currTok.mLine = 0;
        currTok.mColumn = 0;
    }

    bool Lexer::checkKeyword(Token& currTok) {
        if (mKeywords.find(currTok.mLexeme) != mKeywords.end()) {
            return true;
        }
        return false;
    }

    bool Lexer::checkType(Token& currTok) {
        if (mTypes.find(currTok.mLexeme) != mTypes.end()) {
            return true;
        }
        return false;
    }

    void Token::debugPrint() {
        cout << "(TYPE: " << sTokenTypeStrings[mType] << ", VALUE: " << mLexeme << ", LINE: " << mLine << ", COLUMN: " << mColumn<< ")" << endl;
    }
}