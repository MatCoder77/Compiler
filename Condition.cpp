#include "Condition.hpp"

Condition::Condition() {}

Condition::Condition(Condition::Type type, Variable leftHandSide, Variable rightHandSide) {
    this->type = type;
    this->leftHandSide = leftHandSide;
    this->rightHandSide = rightHandSide;
}

ConditionBlock Condition::evaluateCondition(Register r1, Register r2) {
    CodeBlock codeBlock = leftHandSide.loadValueToRegister(r1);
    codeBlock.append(rightHandSide.loadValueToRegister(r2));

    string IF_TRUE_LABEL = CodeBlock::createUniqueLabel();
    string IF_FALSE_LABEL = CodeBlock::createUniqueLabel();

    switch (type) {
        case EQUAL: {
            string LABEL_1 = CodeBlock::createUniqueLabel();

            codeBlock.addCOPY(D, r1);
            codeBlock.addSUB(D, r2);
            codeBlock.addJZERO(D, LABEL_1);
            codeBlock.addJUMP(IF_FALSE_LABEL);
            codeBlock.addLABEL(LABEL_1);
            codeBlock.addCOPY(D, r2);
            codeBlock.addSUB(D, r1);
            codeBlock.addJZERO(D, IF_TRUE_LABEL);
            codeBlock.addJUMP(IF_FALSE_LABEL);
            break;
        }

        case NOT_EQUAL: {
            string LABEL_1 = CodeBlock::createUniqueLabel();

            codeBlock.addCOPY(D, r1);
            codeBlock.addSUB(D, r2);
            codeBlock.addJZERO(D, LABEL_1);
            codeBlock.addJUMP(IF_TRUE_LABEL);
            codeBlock.addLABEL(LABEL_1);
            codeBlock.addCOPY(D, r2);
            codeBlock.addSUB(D, r1);
            codeBlock.addJZERO(D, IF_FALSE_LABEL);
            codeBlock.addJUMP(IF_TRUE_LABEL);
            break;
        }

        case GREATER: {
            codeBlock.addCOPY(D, r1);
            codeBlock.addSUB(D, r2);
            codeBlock.addJZERO(D, IF_FALSE_LABEL);
            codeBlock.addJUMP(IF_TRUE_LABEL);
            break;
        }

        case LESSER: {
            codeBlock.addCOPY(D, r2);
            codeBlock.addSUB(D, r1);
            codeBlock.addJZERO(D, IF_FALSE_LABEL);
            codeBlock.addJUMP(IF_TRUE_LABEL);
            break;
        }

        case GREATER_EQUAL: {
            codeBlock.addCOPY(D, r2);
            codeBlock.addSUB(D, r1);
            codeBlock.addJZERO(D, IF_TRUE_LABEL);
            codeBlock.addJUMP(IF_FALSE_LABEL);
            break;
        }

        case LESSER_EQUAL: {
            codeBlock.addCOPY(D, r1);
            codeBlock.addSUB(D, r2);
            codeBlock.addJZERO(D, IF_TRUE_LABEL);
            codeBlock.addJUMP(IF_FALSE_LABEL);
            break;
        }
    }

    return ConditionBlock(codeBlock, IF_TRUE_LABEL, IF_FALSE_LABEL);
}