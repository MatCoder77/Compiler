#include "VariableManager.hpp"

VariableManager::VariableManager() {
    nextFreeAdressPointer = 0;
}

bool VariableManager::isAlreadyDeclared(string identifier) {
    auto it = declaredSymbols.find(identifier);
    if(it != declaredSymbols.end()) {
        return true;
    }
    return false;
}

bool VariableManager::declare(Variable& variable) {
    string identifier = variable.getIdentifier();
    if(!isAlreadyDeclared(identifier)) {
        variable.setAddress(nextFreeAdressPointer);
        declaredSymbols[identifier] = variable;
        nextFreeAdressPointer += variable.getSize();
        return true;
    }
    return false;
}

bool VariableManager::undeclare(Variable& variable) {
    string identifier = variable.getIdentifier();
    if(isAlreadyDeclared(identifier)) {
        declaredSymbols.erase(identifier);
        return true;
    }
    return false;
}

Variable VariableManager::getDeclaredVariable(string identifier) {
    return declaredSymbols.at(identifier);
}

void VariableManager::markAsInitialized(string identifier) {
    declaredSymbols.at(identifier).setInitialized(true);
}