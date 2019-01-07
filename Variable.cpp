//
// Created by mateusz on 02.01.19.
//

#include "Variable.hpp"

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

Variable::Variable(Variable owningArray, string indexInOwningArrayIdentifier) {
    this->type = ARRAY_ELEMENT_VAR_INDEX;
    this->identifier = owningArray.getIdentifier();
    this->firstIndex = owningArray.getFirstIndex();
    this->lastIndex = owningArray.getLastIndex();
    this->size = lastIndex - firstIndex + 1;
    this->isIterator = false;
    this->isInitialized = true;
    this->indexInOwningArrayIdentifier = indexInOwningArrayIdentifier;
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