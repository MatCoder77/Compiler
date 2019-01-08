#include "Assignment.hpp"

Assignment::Assignment(Variable variable, Expression expression) {
    this->variable = variable;
    this->expression = expression;
}

void Assignment::compile() {
    codeBlock = expression.loadResultToRegister(B);
    codeBlock.append(variable.loadAddressToRegister(A));
    codeBlock.addSTORE(B);
}