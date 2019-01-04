#ifndef COMPILER_CONDITION_HPP
#define COMPILER_CONDITION_HPP

#include <memory>
#include "Variable.hpp"

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

private:
    Type type;
    Variable leftHandSide;
    Variable rightHandSide;
};

using ConditionPointer = shared_ptr<Condition>;

#endif //COMPILER_CONDITION_HPP
