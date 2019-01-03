#ifndef COMPILER_PARSINGDRIVER_HPP
#define COMPILER_PARSINGDRIVER_HPP

#include <string>
#include <cstddef>
#include <iostream>

#include "Scanner.hpp"
#include "parser.tab.hh"

using  namespace std;

namespace yy {

    class ParsingDriver {
    public:
        virtual ~ParsingDriver();
        void parse(const char *const filename);
        ostream& print(std::ostream &stream);
    private:

        yy::Scanner* scanner = nullptr;
        yy::Parser* parser = nullptr;
    };
}
#endif //COMPILER_PARSINGDRIVER_HPP
