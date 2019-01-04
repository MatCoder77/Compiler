#ifndef COMPILER_VARIABLE_HPP
#define COMPILER_VARIABLE_HPP

#include <string>

using namespace std;

class Variable {
public:
    enum Type {
        NUMBER,
        VARIABLE,
        ARRAY
    };

    Variable(){}
    Variable(string identifier);
    Variable(long long value);
    Variable(string identifier, long long begin, long long end) {}
    ~Variable(){};

    string getIdentifier();
    long long getValue();
    Type getType();
private:
    Type type;
    string identifier;
    long long value;
    long long address;
};


#endif //COMPILER_VARIABLE_HPP
