#include "ForLoop.hpp"
#include "Condition.hpp"

ForLoop::ForLoop(Variable iterator, Variable counter, Variable rangeBegin, ForLoop::Type type, Variable rangeEnd, CommandPointers commands) {
    this->iterator = iterator;
    this->counter = counter;
    this->rangeBegin = rangeBegin;
    this->rangeEnd = rangeEnd;
    this->type = type;
    this->commands = commands;
}

void ForLoop::compile() {
    codeBlock = rangeBegin.loadValueToRegister(B);
    codeBlock.append(iterator.loadAddressToRegister(A));
    codeBlock.addSTORE(B);

    switch (type) {
        case TO: {
            codeBlock.append(rangeEnd.loadValueToRegister(C));
            codeBlock.addINC(C);
            codeBlock.addSUB(C, B);
            codeBlock.append(counter.loadAddressToRegister(A));
            codeBlock.addSTORE(C);
            break;
        }
        case DOWNTO: {
            codeBlock.append(rangeEnd.loadValueToRegister(C));
            codeBlock.addINC(B);
            codeBlock.addSUB(B, C);
            codeBlock.append(counter.loadAddressToRegister(A));
            codeBlock.addSTORE(B);
            break;
        }
    }

    string LOOP_BEGIN_LABEL = CodeBlock::createUniqueLabel();
    string LOOP_END_LABEL = CodeBlock::createUniqueLabel();

    codeBlock.addLABEL(LOOP_BEGIN_LABEL);
    codeBlock.append(counter.loadValueToRegister(B));
    codeBlock.addJZERO(B, LOOP_END_LABEL);

    for(auto& cmd: commands) {
        cmd->compile();
        codeBlock.append(cmd->getCodeBlock());
    }

    codeBlock.append(iterator.loadValueToRegister(B));

    switch (type) {
        case TO: {
            codeBlock.addINC(B);
            break;
        }
        case DOWNTO: {
            codeBlock.addDEC(B);
            break;
        }
    }

    codeBlock.append(iterator.loadAddressToRegister(A));
    codeBlock.addSTORE(B);

    codeBlock.append(counter.loadValueToRegister(B));
    codeBlock.addDEC(B);
    codeBlock.append(counter.loadAddressToRegister(A));
    codeBlock.addSTORE(B);

    codeBlock.addJUMP(LOOP_BEGIN_LABEL);
    codeBlock.addLABEL(LOOP_END_LABEL);

}