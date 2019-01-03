//
// Created by mateusz on 02.01.19.
//

#ifndef COMPILER_EXPRESSION_HPP
#define COMPILER_EXPRESSION_HPP

#include "Variable.hpp"

class Expression {
public:
    enum Type {
        VARIABLE,
        ADDITION,
        SUBTRACTION,
        MULTIPLICATION,
        DIVISION,
        MODULO
    };
    Expression();
    Expression(Variable variable);
    Expression(Type type, Variable variable1, variable2);

private:
    Type type;
    Variable variable1;
    Variable variable2;
};


#endif //COMPILER_EXPRESSION_HPP
