#include "Write.hpp"

Write::Write(Variable variable) {
    this->variable = variable;
}

void Write::compile() {
    codeBlock = variable.loadValueToRegister(B);
    codeBlock.addPUT(B);
}