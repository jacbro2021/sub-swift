#ifndef KEYWORD_HPP
#define KEYWORD_HPP

#include <string>

namespace lexer {

    using namespace std;

    enum BUILTIN_KEYWORD {
        NONE_KW, // Default, not to be used.
        LET,
        VAR,
        FUNC,
        RETURN,
    };

    class Keyword {
    public:
        Keyword(const string& name = "", enum BUILTIN_KEYWORD type = NONE_KW) : mName(name), mType(type) {};
        string mName;
        enum BUILTIN_KEYWORD mType;
    };

}

#endif