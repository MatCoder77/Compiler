#include "Write.hpp"

Write::Write(Variable variable) {
    this->variable = variable;
}

void Write::compile() {
    cout << "WRITE variable" << endl;
}