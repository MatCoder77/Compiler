#include "Assignment.hpp"

Assignment::Assignment(Variable variable, Expression expression) {
    this->variable = variable;
    this->expression = expression;
}

void Assignment::compile() {
    cout << variable.getIdentifier() << " := " << "expression" << endl;
}