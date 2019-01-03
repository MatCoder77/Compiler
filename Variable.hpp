//
// Created by mateusz on 02.01.19.
//

#ifndef COMPILER_VARIABLE_HPP
#define COMPILER_VARIABLE_HPP

#include <string>

using namespace std;

class Variable {
public:
    Variable(){}
    Variable(string identifier);
    Variable(long long value);
    ~Variable(){};

private:
    string identifier;
    long long value;
};


#endif //COMPILER_VARIABLE_HPP
