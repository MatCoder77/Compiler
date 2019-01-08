//
// Created by mateusz on 02.01.19.
//

#ifndef COMPILER_EXPRESSION_HPP
#define COMPILER_EXPRESSION_HPP

#include <iostream>
#include "Variable.hpp"
#include "CodeBlock.hpp"

using namespace std;

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
    Expression(Type type, Variable leftHandSide, Variable rightHandSide);

    void compile();
    Variable getLeftHandSide();
    Variable getRightHandSide();
    Type getType();
    string getTypeString();
    string getExpressionString();
    CodeBlock loadResultToRegister(Register reg);
private:
    Type type;
    Variable leftHandSide;
    Variable rightHandSide;
};


#endif //COMPILER_EXPRESSION_HPP
