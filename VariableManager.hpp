//
// Created by mateusz on 02.01.19.
//

#ifndef COMPILER_SYMBOLSTABLE_HPP
#define COMPILER_SYMBOLSTABLE_HPP

#include <unordered_map>
#include <string>
#include "Variable.hpp"
#include <iostream>

using namespace std;

class VariableManager {
public:
    VariableManager();
    bool declare(Variable& variable);
    bool isAlreadyDeclared(string identifier);
    bool undeclare(Variable& variable);
    Variable getDeclaredVariable(string identifier);
    void markAsInitialized(string identifier);
private:
    unordered_map <string, Variable> declaredSymbols;
    long long nextFreeAdressPointer;
};


#endif //COMPILER_SYMBOLSTABLE_HPP
