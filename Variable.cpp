//
// Created by mateusz on 02.01.19.
//

#include "Variable.hpp"

Variable::Variable(string identifier) {
    this->type = VARIABLE;
    this->identifier = identifier;
}

Variable::Variable(long long value) {
    this->type = NUMBER;
    this->value = value;
}

string Variable::getIdentifier() {
    return identifier;
}

long long Variable::getValue() {
    return value;
}

Variable::Type Variable::getType() {
    return type;
}