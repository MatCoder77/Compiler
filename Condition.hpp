#ifndef COMPILER_CONDITION_HPP
#define COMPILER_CONDITION_HPP

#include <memory>
#include "Variable.hpp"

class ConditionBlock {
public:
    ConditionBlock(CodeBlock codeBlock, string IF_TRUE_LABEL, string IF_FALSE_LABEL) {
        this->codeBlock = codeBlock;
        this->IF_TRUE_LABEL = IF_TRUE_LABEL;
        this->IF_FLASE_LABEL = IF_FALSE_LABEL;
    }

    CodeBlock getCodeBlock() {
        return codeBlock;
    }

    string getIfFalseLabel() {
        return IF_FLASE_LABEL;
    }

    string getIfTrueLabel() {
        return IF_TRUE_LABEL;
    }

private:
    CodeBlock codeBlock;
    string IF_TRUE_LABEL;
    string IF_FLASE_LABEL;
};

class Condition {
public:
    enum Type {
        EQUAL,
        NOT_EQUAL,
        GREATER,
        LESSER,
        GREATER_EQUAL,
        LESSER_EQUAL
    };

    Condition();
    Condition(Type type, Variable leftHandSide, Variable rightHandSide);

    ConditionBlock evaluateCondition(Register r1, Register r2);
private:
    Type type;
    Variable leftHandSide;
    Variable rightHandSide;
};



using ConditionPointer = shared_ptr<Condition>;

#endif //COMPILER_CONDITION_HPP
