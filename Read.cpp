#include "Read.hpp"

Read::Read(Variable variable) {
    this->variable = variable;
}

void Read::compile() {
    cout << "READ variable" << endl;
}