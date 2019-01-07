#ifndef COMPILER_PARSINGDRIVER_HPP
#define COMPILER_PARSINGDRIVER_HPP

#include <string>
#include <cstddef>
#include <iostream>
#include <stdexcept>

#include "Scanner.hpp"
#include "parser.tab.hh"

#include "VariableManager.hpp"

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
        Variable getElementFromDeclaredArray(string identifier, string variableWithIndex);
        void checkCondition(bool condition, string errorMessage);
        void markVariableAsInitialized(string identifier);
    private:

        yy::Scanner* scanner = nullptr;
        yy::Parser* parser = nullptr;
        VariableManager variableManager;
    };
}
#endif //COMPILER_PARSINGDRIVER_HPP
