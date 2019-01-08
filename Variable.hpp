#ifndef COMPILER_VARIABLE_HPP
#define COMPILER_VARIABLE_HPP

#include <string>
#include "CodeBlock.hpp"
#include <iostream>

using namespace std;

class Variable {
public:
    enum Type {
        NUMBER,
        VARIABLE,
        ARRAY,
        ARRAY_ELEMENT_FIXED_INDEX,
        ARRAY_ELEMENT_VAR_INDEX
    };
    Variable(){}
    Variable(string identifier, bool isIterator = false);
    Variable(long long value);
    Variable(string identifier, long long begin, long long end);
    Variable(Variable owningArray, long long indexInOwningArray);
    Variable(Variable owningArray, Variable indexInOwningArrayVariable);
    ~Variable(){};

    string getIdentifier();
    long long getValue();
    Type getType();
    long long getAddress();
    void setAddress(long long address);
    long long getFirstIndex();
    long long getLastIndex();
    long long getIndexInOwningArray();
    long long getSize();
    bool isDeclaredAsIterator();
    bool isVariableInitialized();
    void setInitialized(bool initialized);
    string getIndexInOwningArrayIdentifier();
    static CodeBlock generateNumberInRegister(long long number, Register reg);
    CodeBlock loadValueToRegister(Register reg);
    CodeBlock loadAddressToRegister(Register reg = Register::A);
private:
    Type type;
    string identifier;
    long long value;
    long long address;
    long long firstIndex;
    long long lastIndex;
    long long size;
    bool isIterator;
    bool isInitialized;
    long long indexInOwningArray;
    string indexInOwningArrayIdentifier;
    long long addressOfIndexInOwningArrayIdentifier;
    long long owningArrayAddress;
};


#endif //COMPILER_VARIABLE_HPP
