%{
#include <string>
#include "Scanner.hpp"
#include "Variable.hpp"
#include "Condition.hpp"
#include "Expression.hpp"
#include "Command.hpp"
#include "WhileLoop.hpp"
#include "Write.hpp"
#include "Assignment.hpp"
#include "DoWhileLoop.hpp"
#include "ForLoop.hpp"
#include "IfStatement.hpp"
#include "IfElseStatement.hpp"
#include "Read.hpp"
#include "CodeBlock.hpp"

#undef  YY_DECL
#define YY_DECL int yy::Scanner::yylex(yy::Parser::semantic_type* const lval, yy::Parser::location_type *loc)

using token = yy::Parser::token;

#define yyterminate() return( token::ENDSCANN )

#define YY_USER_ACTION loc->step(); loc->columns(yyleng);

%}

%option debug
%option nodefault
%option yyclass="yy::Scanner"
%option noyywrap
%option c++

%x COMMENT

%%

%{          /** Code executed at the beginning of yylex **/
            yylval = lval;
	    this->loc = loc;
%}

"[" 		  { BEGIN(COMMENT); }
<COMMENT>"]"      { BEGIN(INITIAL); }
<COMMENT>\n       { loc->lines(yyleng); }
<COMMENT>.        {}
<COMMENT><<EOF>>  { return token::ERROR; }

[0-9]+ 	    	  { yylval->build< std::string >( yytext ); return(token::NUMBER);}
[_a-z]+     	  { yylval->build< std::string >( yytext ); return(token::PIDENTIFIER); }

"DECLARE"   	  { return token::DECLARE; }
"IN"        	  { return token::IN; }
"END"       	  { return token::END; }

"IF"        	  { return token::IF; }
"THEN"      	  { return token::THEN; }
"ELSE"      	  { return token::ELSE ; }
"ENDIF"     	  { return token::ENDIF;}

"WHILE"     	  { return token::WHILE; }
"DO"        	  { return token::DO; }
"ENDWHILE"  	  { return token::ENDWHILE; }
"ENDDO"     	  { return token::ENDDO; }

"FOR"       	  { return token::FOR; }
"FROM"      	  { return token::FROM; }
"TO"        	  { return token::TO; }
"DOWNTO"    	  { return token::DOWNTO; }
"ENDFOR"    	  { return token::ENDFOR; }

"READ"      	  { return token::READ; }
"WRITE"     	  { return token::WRITE; }

"("         	  { return token::LEFT_BRACE; }
")"         	  { return token::RIGHT_BRACE; }

"+"	          { return token::ADD; }
"-"	          { return token::SUB; }
"*"	          { return token::MUL; }
"/"	          { return token::DIV; }
"%"	          { return token::MOD; }
":="        	  { return(token::ASSIGNMENT); }

"="         	  { return token::EQUAL; }
"!="        	  { return token::NOT_EQUAL; }
"<"         	  { return token::LESSER; }
">"         	  { return token::GREATER; }
"<="        	  { return token::LESSER_EQUAL; }
">="        	  { return token::GREATER_EQUAL; }

";"         	  { return token::SEMICOLON; }
":"         	  { return token::COLON; }
\n          	  { loc->lines(yyleng);}
[ \n\t\r]   	  {}
.	          { return token::ERROR; }

<<EOF>>           { yyterminate(); }

%%
