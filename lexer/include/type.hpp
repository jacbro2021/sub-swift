#ifndef TYPE_HPP
#define TYPE_HPP

#include <string>
#include <vector>

namespace lexer {
    using namespace std;

    enum BUILTIN_TYPE {
        NONE_T, // Defualt, not to be used.
        INT,
        DOUBLE,
        STRING,
    };

    class Type {
    public:
        Type(const string& name = "", enum BUILTIN_TYPE type = NONE_T) : mName(name), mType(type) {}
        string mName;
        enum BUILTIN_TYPE mType;
    };
}

#endif