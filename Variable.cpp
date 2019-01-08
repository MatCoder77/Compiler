//
// Created by mateusz on 02.01.19.
//

#include "Variable.hpp"
#include "CodeBlock.hpp"

Variable::Variable(string identifier, bool isIterator) {
    this->type = VARIABLE;
    this->identifier = identifier;
    this->size = 1;
    this->isIterator = isIterator;
    this->isInitialized = isIterator;
}

Variable::Variable(long long value) {
    this->type = NUMBER;
    this->value = value;
    this->size = 1;
    this->isIterator = false;
    this->isInitialized = true;
}

Variable::Variable(string identifier, long long begin, long long end) {
    this->type = ARRAY;
    this->identifier = identifier;
    this->firstIndex = begin;
    this->lastIndex = end;
    this->size = end - begin + 1;
    this->isIterator = false;
    this->isInitialized = true;
}

Variable::Variable(Variable owningArray, long long indexInOwningArray) {
    this->type = ARRAY_ELEMENT_FIXED_INDEX;
    this->identifier = owningArray.getIdentifier();
    this->firstIndex = owningArray.getFirstIndex();
    this->lastIndex = owningArray.getLastIndex();
    this->size = lastIndex - firstIndex + 1;
    this->isIterator = false;
    this->isInitialized = true;
    this->indexInOwningArray = indexInOwningArray;
}

Variable::Variable(Variable owningArray, Variable indexInOwningArrayVariable) {
    this->type = ARRAY_ELEMENT_VAR_INDEX;
    this->identifier = owningArray.getIdentifier();
    this->firstIndex = owningArray.getFirstIndex();
    this->lastIndex = owningArray.getLastIndex();
    this->size = lastIndex - firstIndex + 1;
    this->isIterator = false;
    this->isInitialized = true;
    this->indexInOwningArrayIdentifier = indexInOwningArrayVariable.getIdentifier();
    this->addressOfIndexInOwningArrayIdentifier = indexInOwningArrayVariable.getAddress();
    this->owningArrayAddress = owningArray.getAddress();
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

long long Variable::getAddress() {
    return address;
}

void Variable::setAddress(long long address) {
    this->address = address;
}

long long Variable::getFirstIndex() {
    return firstIndex;
}

long long Variable::getLastIndex() {
    return lastIndex;
}

long long Variable::getIndexInOwningArray() {
    return indexInOwningArray;
}

string Variable::getIndexInOwningArrayIdentifier() {
    return indexInOwningArrayIdentifier;
}

long long Variable::getSize() {
    return  size;
}

bool Variable::isDeclaredAsIterator() {
    return isIterator;
}

bool Variable::isVariableInitialized() {
    return  isInitialized;
}

void Variable::setInitialized(bool initialized) {
    isInitialized = initialized;
}

CodeBlock Variable::generateNumberInRegister(long long number, Register reg) {
    CodeBlock codeBlock;
    vector<int> reminders;

    while(number) {
        reminders.push_back(number % 2);
        number /= 2;
    }

    codeBlock.addSUB(reg, reg);
    for(int i = reminders.size() - 1; i >= 0; i--) {
        if(reminders[i]) {
            codeBlock.addINC(reg);
        }
        if(i) {
            codeBlock.addADD(reg, reg);
        }
    }
    return codeBlock;
}

CodeBlock Variable::loadValueToRegister(Register reg) {
    CodeBlock codeBlock;
    if(type == NUMBER) {
        codeBlock = generateNumberInRegister(value, reg);
    }
    else if(type == VARIABLE || type == ARRAY_ELEMENT_VAR_INDEX || type == ARRAY_ELEMENT_FIXED_INDEX) {
        codeBlock = loadAddressToRegister(A);
        codeBlock.addLOAD(reg);
    }
    else {
        cout << "Called load value for variable of type ARRAY" << endl;
        exit(1);
    }
    return codeBlock;
}

CodeBlock Variable::loadAddressToRegister(Register reg) {
    CodeBlock codeBlock;
    if(type == VARIABLE || type == ARRAY || type == ARRAY_ELEMENT_FIXED_INDEX) {
        codeBlock = generateNumberInRegister(address, reg);
    }
    else if(type == ARRAY_ELEMENT_VAR_INDEX) {
        codeBlock = generateNumberInRegister(addressOfIndexInOwningArrayIdentifier, A);
        codeBlock.addLOAD(A);
        CodeBlock loadArrayAddressBlock = generateNumberInRegister(owningArrayAddress, H);
        codeBlock.append(loadArrayAddressBlock);
        codeBlock.addADD(A, H);
        CodeBlock loadFirstIndexValueBlock = generateNumberInRegister(firstIndex, H);
        codeBlock.append(loadFirstIndexValueBlock);
        codeBlock.addSUB(A, H);
        if(reg != A) {
            codeBlock.addCOPY(reg, A);
        }
    } else {
        cout << "Called get address for variable of TYPE NUMBER" << endl;
        exit(1);
    }
    return codeBlock;
}