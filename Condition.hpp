//
// Created by mateusz on 02.01.19.
//

#ifndef COMPILER_CONDITION_HPP
#define COMPILER_CONDITION_HPP

#include "Variable.hpp"

class Condition {
public:
    enum Type {
        EQUAL,
        NOT_EQUAL,
        GREATER,
        LESSER,
        GREATER_EQUAL,
        LESSER_EQUAL
    };

    Condition();
    Condition(Type type, Variable variable1, Variable variable2);

private:
    Type type;
    Variable variable1;
    Variable variable2;
};


#endif //COMPILER_CONDITION_HPP
