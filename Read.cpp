#include "Read.hpp"

Read::Read(Variable variable) {
    this->variable = variable;
}

void Read::compile() {
    codeBlock.addGET(B);
    CodeBlock loadVarAddressBlock = variable.loadAddressToRegister(A);
    codeBlock.append(loadVarAddressBlock);
    codeBlock.addSTORE(B);
}