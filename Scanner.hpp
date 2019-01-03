#ifndef COMPILER_SCANNER_HPP
#define COMPILER_SCANNER_HPP

#ifndef yyFlexLexerOnce
#include <FlexLexer.h>
#endif

#include <iostream>
#include "parser.tab.hh"
#include "location.hh"

using  namespace std;

namespace yy {

    class Scanner : public yyFlexLexer {
    public:
        Scanner(istream *input) : yyFlexLexer(input) {}
        using FlexLexer::yylex;
        virtual int yylex(yy::Parser::semantic_type* const lval, yy::Parser::location_type *loc);
    private:
        yy::Parser::semantic_type *yylval = nullptr;
    };

}

#endif //COMPILER_SCANNER_HPP
