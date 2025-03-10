#ifndef TOKENIZER_HPP
#define TOKENIZER_HPP   

#include <string>
#include <vector>

namespace lexer {
    
    using namespace std;

    enum TokenType {
       WHITESPACE,  
       COMMENT,
       IDENTIFIER,
       OPERATOR,
       PUNCTUATOR,
       STRING_LITERAL,
       NUMBER_LITERAL,
       INTEGER_LITERAL,
       FLOAT_LITERAL,
    };

    static const char* sTokenTypeStrings[] = {
        "WHITESPACE",
        "COMMENT",
        "IDENTIFIER",
        "OPERATOR",
        "PUNCTUATOR",
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
    };

    class Lexer {
    public:
        vector<Token> runLexer(const string& source);
    private:
        void endToken(Token& currTok, vector<Token>& tokens);
    };
}

#endif