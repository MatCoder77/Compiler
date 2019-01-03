#include "Condition.hpp"

Condition::Condition() {}

Condition::Condition(Condition::Type type, Variable variable1, Variable variable2) {
    this->type = type;
    this->variable1 = variable1;
    this->variable2 = variable2;
}