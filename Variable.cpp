//
// Created by mateusz on 02.01.19.
//

#include "Variable.hpp"

Variable::Variable(string identifier) {
    this->identifier = identifier;
}

Variable::Variable(long long value) {
    this->value = value;
}