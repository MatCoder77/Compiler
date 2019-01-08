#include "ParsingDriver.hpp"

#include <fstream>
#include <sstream>
#include <regex>

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

Variable yy::ParsingDriver::getElementFromDeclaredArray(string identifier, Variable variableWithIndex) {
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

void yy::ParsingDriver::setCommands(CommandPointers commands) {
    this->programCommands = commands;
}

void yy::ParsingDriver::compile(const char *const filename) {
    for(auto& cmd : programCommands) {
        cmd->compile();
        programCode.append(cmd->getCodeBlock());
    }

    programCode.addHALT();

    long long lineNumber;

    ofstream outputFileRaw("raw.txt");

    for(auto& instruction : programCode.getCode()) {
        outputFileRaw << instruction << "\n";
    }

    outputFileRaw.close();

    for(long long i = 0; i < programCode.getCode().size(); i++) {
        if(programCode.getCode()[i].find('#') != string::npos) {
            lineNumber = i;
            string cmd = programCode.getCode()[i];
            string labelID = cmd.substr(cmd.find('#') + 1);
            string label = "$";
            label += labelID;
            programCode.getCode().erase(programCode.getCode().begin() + i);
            for(long long k = 0; k < programCode.getCode().size(); k++) {
                if(programCode.getCode()[k].find(label) != string::npos) {
                    string jumpCmd = programCode.getCode()[k];
                    string escapedLabel = "\\$";
                    escapedLabel += labelID;
                    escapedLabel += "$";
                    string newCmd = std::regex_replace(jumpCmd, std::regex(escapedLabel), to_string(lineNumber));
                    programCode.getCode()[k] = newCmd;
                }
            }
        }
    }
    //labels resolution

    ofstream outputFile(filename);

    for(auto& instruction : programCode.getCode()) {
        outputFile << instruction << "\n";
    }

    outputFile.close();

}

void yy::ParsingDriver::saveToFile(const char *const filename) {

}

ostream& yy::ParsingDriver::print(std::ostream &stream) {
    stream << "Compilled succesfully!" << endl;
    return stream;
}