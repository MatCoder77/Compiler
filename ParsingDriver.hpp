#ifndef COMPILER_PARSINGDRIVER_HPP
#define COMPILER_PARSINGDRIVER_HPP

#include <string>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include <sstream>

#include "Scanner.hpp"
#include "parser.tab.hh"

#include "VariableManager.hpp"
#include "Command.hpp"
#include "CodeBlock.hpp"

using  namespace std;

namespace yy {

    class ParsingDriver {
    public:
        virtual ~ParsingDriver();
        void parse(const char *const filename);
        ostream& print(std::ostream &stream);
        void declare(Variable& variable);
        void undeclare(Variable& variable);
        Variable getDeclaredVariable(string identifier);
        Variable getElementFromDeclaredArray(string identifier, long long index);
        Variable getElementFromDeclaredArray(string identifier, Variable variableWithIndex);
        void checkCondition(bool condition, string errorMessage);
        void markVariableAsInitialized(string identifier);
        void setCommands(CommandPointers commands);
        void compile(const char *const filename);
        void saveToFile(const char *const filename);
    private:

        yy::Scanner* scanner = nullptr;
        yy::Parser* parser = nullptr;
        VariableManager variableManager;
        CommandPointers  programCommands;
        CodeBlock programCode;
    };
}
#endif //COMPILER_PARSINGDRIVER_HPP
