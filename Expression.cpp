#include "Expression.hpp"

Expression::Expression() {}

Expression::Expression(Variable variable) {
    this->type = VARIABLE;
    this->leftHandSide = variable;
}

Expression::Expression(Expression::Type type, Variable leftHandSide, Variable rightHandSide) {
    this->type = type;
    this->leftHandSide = leftHandSide;
    this->rightHandSide = rightHandSide;
}

void Expression::compile() {
    cout << "expression";
}

Variable Expression::getLeftHandSide() {
    return leftHandSide;
}

Variable Expression::getRightHandSide() {
    return rightHandSide;
}

Expression::Type Expression::getType() {
    return type;
}

string Expression::getTypeString() {
    switch (type) {
        case VARIABLE:
            return "";
        case ADDITION:
            return "+";
        case MULTIPLICATION:
            return "*";
        case SUBTRACTION:
            return "-";
        case DIVISION:
            return "/";
        case MODULO:
            return "%";
    }
    return "ERROR";
}

string Expression::getExpressionString() {
    return "TODO";
}