#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP   

#include <string>
#include <vector>
#include <map>

#include "keyword.hpp"
#include "type.hpp"

namespace lexer {
    
    using namespace std;

    enum TokenType {
       WHITESPACE,  
       POTENTIAL_COMMENT,
       POTENTIAL_ARROW,
       COMMENT,
       IDENTIFIER,
       OPERATOR,
       PUNCTUATOR,
       KEYWORD,
       TYPE,
       STRING_LITERAL,
       NUMBER_LITERAL,
       INTEGER_LITERAL,
       FLOAT_LITERAL,
    };

    static const char* sTokenTypeStrings[] = {
        "WHITESPACE",
        "POTENTIAL_COMMENT",
        "POTENTIAL_ARROW",
        "COMMENT",
        "IDENTIFIER",
        "OPERATOR",
        "PUNCTUATOR",
        "KEYWORD",
        "TYPE",
        "STRING_LITERAL",
        "NUMBER_LITERAL",
        "INTEGER_LITERAL",
        "FLOAT_LITERAL",
    };

    class Token {
    public: 
        TokenType mType{WHITESPACE};
        string mLexeme;
        int mLine{0};
        int mColumn{0};

        void debugPrint();

    private:
        
    };

    class Lexer {
    public:
        Lexer();
        vector<Token> runLexer(const string& source);
    private:
        map<string, Keyword> mKeywords;
        map<string, Type> mTypes;
        void endToken(Token& currTok, vector<Token>& tokens);
        bool checkKeyword(Token& currTok);
        bool checkType(Token& currTok);
    };
}

#endif