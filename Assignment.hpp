#ifndef COMPILER_ASSIGNMENT_HPP
#define COMPILER_ASSIGNMENT_HPP

#include "Command.hpp"
#include "Variable.hpp"
#include "Expression.hpp"

class Assignment : public Command{
public:
    Assignment(Variable variable, Expression expression);

    void compile();
private:
    Variable variable;
    Expression expression;
};


#endif //COMPILER_ASSIGNMENT_HPP
