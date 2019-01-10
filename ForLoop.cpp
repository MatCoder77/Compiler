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
    switch (type) {
        case TO: {
            codeBlock = rangeBegin.loadValueToRegister(B);
            codeBlock.append(iterator.loadAddressToRegister(A));
            codeBlock.addSTORE(B);

            codeBlock.append(rangeEnd.loadValueToRegister(C));
            codeBlock.append(counter.loadAddressToRegister(A));
            codeBlock.addSTORE(C);

            string LOOP_BEGIN_LABEL = CodeBlock::createUniqueLabel();
            string LOOP_END_LABEL = CodeBlock::createUniqueLabel();
            string IF_TRUE_LABEL = CodeBlock::createUniqueLabel();

            codeBlock.addLABEL(LOOP_BEGIN_LABEL);

            codeBlock.addCOPY(D, B);
            codeBlock.addSUB(D, C);
            codeBlock.addJZERO(D, IF_TRUE_LABEL);
            codeBlock.addJUMP(LOOP_END_LABEL);

            codeBlock.addLABEL(IF_TRUE_LABEL);

            for(auto& cmd: commands) {
                cmd->compile();
                codeBlock.append(cmd->getCodeBlock());
            }

            codeBlock.append(iterator.loadValueToRegister(B));
            codeBlock.addINC(B);
            codeBlock.append(iterator.loadAddressToRegister(A));
            codeBlock.addSTORE(B);

            codeBlock.append(counter.loadValueToRegister(C));

            codeBlock.addJUMP(LOOP_BEGIN_LABEL);

            codeBlock.addLABEL(LOOP_END_LABEL);

            break;
        }
        case DOWNTO: {
            codeBlock = rangeBegin.loadValueToRegister(B);
            codeBlock.append(iterator.loadAddressToRegister(A));
            codeBlock.addSTORE(B);

            codeBlock.append(rangeEnd.loadValueToRegister(C));
            codeBlock.addINC(B);
            codeBlock.addSUB(B, C);
            codeBlock.append(counter.loadAddressToRegister(A));
            codeBlock.addSTORE(B);

            string LOOP_BEGIN_LABEL = CodeBlock::createUniqueLabel();
            string LOOP_END_LABEL = CodeBlock::createUniqueLabel();

            codeBlock.addLABEL(LOOP_BEGIN_LABEL);

            codeBlock.addJZERO(B, LOOP_END_LABEL);

            for(auto& cmd: commands) {
                cmd->compile();
                codeBlock.append(cmd->getCodeBlock());
            }

            codeBlock.append(iterator.loadValueToRegister(B));
            codeBlock.addDEC(B);
            codeBlock.append(iterator.loadAddressToRegister(A));
            codeBlock.addSTORE(B);

            codeBlock.append(counter.loadValueToRegister(B));
            codeBlock.addDEC(B);
            codeBlock.append(counter.loadAddressToRegister(A));
            codeBlock.addSTORE(B);
            codeBlock.addJUMP(LOOP_BEGIN_LABEL);

            codeBlock.addLABEL(LOOP_END_LABEL);

            break;
        }
    }
}