#include "ParsingDriver.hpp"

#include <fstream>
#include <sstream>

yy::ParsingDriver::~ParsingDriver() {
    delete(scanner);
    scanner = nullptr;
    delete(parser);
    parser = nullptr;
}

void yy::ParsingDriver::parse(const char *const filename) {
    ifstream file(filename);
    cout << "W parse" << endl;
    if (!file) {
        exit(EXIT_FAILURE);
    }
    scanner = new yy::Scanner(&file);
    parser = new yy::Parser(*scanner, *this);

    if(parser->parse() != 0)
    {
        std::cerr << "Parse failed!!\n";
    }
}

void yy::ParsingDriver::declare(Variable& variable) {
    if(!variableManager.declare(variable)) {
        string message = "Redeclaration of variable ";
        message += variable.getIdentifier();
        parser->error(*(scanner->loc), message);
    }
}

void yy::ParsingDriver::undeclare(Variable& variable) {
    variableManager.undeclare(variable);
}

Variable yy::ParsingDriver::getDeclaredVariable(string identifier) {
    Variable fetchedVariable;
    try {
        fetchedVariable = variableManager.getDeclaredVariable(identifier);
    }
    catch (out_of_range& e) {
        string message = "Undeclared variable ";
        message += identifier;
        parser->error(*(scanner->loc), message);
    }

    return fetchedVariable;
}

Variable yy::ParsingDriver::getElementFromDeclaredArray(string identifier, long long index) {
    Variable declaredArray = getDeclaredVariable(identifier);
    if(declaredArray.getType() != Variable::ARRAY) {
        string message = "Variable ";
        message += declaredArray.getIdentifier();
        message += " is not an array";
        parser->error(*(scanner->loc), message);
    }
    Variable arrayElement(declaredArray, index);
    arrayElement.setAddress(declaredArray.getAddress() + (index - declaredArray.getFirstIndex()));
    return arrayElement;
}

Variable yy::ParsingDriver::getElementFromDeclaredArray(string identifier, string variableWithIndex) {
    Variable declaredArray = getDeclaredVariable(identifier);
    if(declaredArray.getType() != Variable::ARRAY) {
        string message = "Variable ";
        message += declaredArray.getIdentifier();
        message += " is not an array";
        parser->error(*(scanner->loc), message);
    }
    Variable arrayElement(declaredArray, variableWithIndex);
    return arrayElement;
}

void yy::ParsingDriver::checkCondition(bool condition, string errorMessage) {
    if(!condition) {
        parser->error(*(scanner->loc), errorMessage);
    }
}

void yy::ParsingDriver::markVariableAsInitialized(string identifier) {
    try {
        variableManager.markAsInitialized(identifier);
    }
    catch (out_of_range& e) {
        string message = "Undeclared variable ";
        message += identifier;
        parser->error(*(scanner->loc), message);
    }
}

ostream& yy::ParsingDriver::print(std::ostream &stream) {
    stream << "Compilled succesfully!" << endl;
    return stream;
}