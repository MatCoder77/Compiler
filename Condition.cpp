#include "Condition.hpp"

Condition::Condition() {}

Condition::Condition(Condition::Type type, Variable leftHandSide, Variable rightHandSide) {
    this->type = type;
    this->leftHandSide = leftHandSide;
    this->rightHandSide = rightHandSide;
}