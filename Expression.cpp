#include "Expression.hpp"

Expression::Expression() {}

Expression::Expression(Variable variable) {
    type = VARIABLE;
    variable1 = variable;
}

Expression::Expression(Expression::Type type, Variable variable1, variable2) {
    this->type = type;
    this->variable1 = variable1;
    this->variable2 = variable2;
}