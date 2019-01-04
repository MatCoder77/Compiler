%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%define parser_class_name 	{ Parser }
%parse-param 			{ Scanner& scanner  }
%parse-param 			{ ParsingDriver& parsingDriver  }

%code requires{
   namespace yy {
      class ParsingDriver;
      class Scanner;
   }

   #include <iostream>
   #include <string>
   #include <vector>
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
}

%code{
   #include <iostream>
   #include <cstdlib>
   #include <fstream>
   #include <string>
   #include <stdlib.h>
   #include <vector>
   #include "ParsingDriver.hpp"
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

#undef yylex
#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert

%type <Variable> identifier
%type <Variable> value
%type <Expression> expression
%type <ConditionPointer> condition
%type <CommandPointer> command
%type <CommandPointers> commands

%token <std::string>  NUMBER
%token <std::string>  PIDENTIFIER

%token      ERROR

%token      SEMICOLON COLON LEFT_BRACE RIGHT_BRACE ASSIGNMENT
%token      EQUAL NOT_EQUAL LESSER GREATER LESSER_EQUAL GREATER_EQUAL

%token      DECLARE IN IF THEN ELSE ENDIF WHILE DO ENDWHILE ENDDO FOR FROM TO ENDFOR DOWNTO READ WRITE END
%token      ENDSCANN      0     "end of file"

%left       ADD SUB
%left       MUL DIV MOD


%locations


%%

program
   : DECLARE declarations IN commands END 			{ 
									std::cout<<"Parsing..." << endl;
									cout << $4.size() << endl;
									for( auto c : $4) {
									    c->compile();
									}
					  			}
   ;

declarations
   : %empty
   | declarations PIDENTIFIER SEMICOLON
   | declarations PIDENTIFIER LEFT_BRACE NUMBER COLON NUMBER RIGHT_BRACE SEMICOLON
   ;

commands
   : commands command 						{ 
									cout << "dodaje komendy" << endl;
									$1.push_back($2);
									$$ = $1;
								}
   | command 							{ 
									cout << "dodaje komende" << endl;
									$$.push_back($1);
								}
   ;

command
   : identifier ASSIGNMENT expression SEMICOLON 		{
         								$$ = std::make_shared<Assignment>($1, $3);
      								}
   | IF condition THEN commands ELSE commands ENDIF 		{
									cout << "Czytam IfElse" << endl;
									$$ = make_shared<IfElseStatement>($2, $4, $6);
      								}
   | IF condition THEN commands ENDIF 				{
									cout << "Czytam If" << endl;
									$$ = make_shared<IfStatement>($2, $4);
      								}
   | WHILE condition DO commands ENDWHILE 			{
									cout << "Czytam whilea" << endl;
									$$ = std::make_shared<WhileLoop>($2, $4);
      								}
   | DO commands WHILE condition ENDDO 				{
									cout << "Czytam dowhile" << endl;
									$$ = make_shared<DoWhileLoop>($2, $4);
      								}
   | FOR PIDENTIFIER FROM value TO value DO commands ENDFOR 	{
									cout << "Czytam For to" << endl;
									$$ = make_shared<ForLoop>($2, $4, ForLoop::Type::TO, $6, $8);
      								}
   | FOR PIDENTIFIER FROM value DOWNTO value DO commands ENDFOR	{
									cout << "Czytam For downto" << endl;
									$$ = make_shared<ForLoop>($2, $4, ForLoop::Type::DOWNTO, $6, $8);
      								}
   | READ identifier SEMICOLON 					{
         								cout << "Czytam READ" << endl;
									$$ = make_shared<Read>($2);
      								}
   | WRITE value SEMICOLON 					{
									cout << "Czytam WRITE" << endl;
         								$$ = std::make_shared<Write>($2);	
      								}
   ;

expression
   : value 							{ 
									$$ = Expression($1);
								}
   | value ADD value 						{ 
									$$ = Expression(Expression::Type::ADDITION, $1, $3);
								}
   | value SUB value 						{ 
									$$ = Expression(Expression::Type::SUBTRACTION, $1, $3);
								}
   | value MUL value 						{ 
									$$ = Expression(Expression::Type::MULTIPLICATION, $1, $3);
								}
   | value DIV value 						{ 
									$$ = Expression(Expression::Type::DIVISION, $1, $3);
								}
   | value MOD value 						{ 
									$$ = Expression(Expression::Type::MODULO, $1, $3);
								}
   ;

condition
   : value EQUAL value  					{ 
									cout << "czytam warumek" << endl;
									$$ = std::make_shared<Condition>(Condition::Type::EQUAL, $1, $3);
								}
   | value NOT_EQUAL value 					{ 
									cout << "czytam warumek" << endl;
									$$ = std::make_shared<Condition>(Condition::Type::NOT_EQUAL, $1, $3);
								}
   | value LESSER value   					{ 
									cout << "czytam warumek" << endl;
									$$ = std::make_shared<Condition>(Condition::Type::LESSER, $1, $3);
								}
   | value GREATER value  					{ 
									cout << "czytam warunek" << endl;
									$$ = std::make_shared<Condition>(Condition::Type::GREATER, $1, $3);
								}
   | value LESSER_EQUAL value  					{ 
									cout << "czytam warumek" << endl;
									$$ = std::make_shared<Condition>(Condition::Type::LESSER_EQUAL, $1, $3);
								}
   | value GREATER_EQUAL value 					{ 
									cout << "czytam warumek" << endl;
									$$ = std::make_shared<Condition>(Condition::Type::GREATER_EQUAL, $1, $3);
								}
   ;

value
   : NUMBER 							{ 
									cout << "czytam stałą" << endl;
									long long var = std::stoll($1);
									$$ = Variable(var);
								}
   | identifier 						{ 
									$$ = $1;
								}
   ;

identifier
   : PIDENTIFIER 						{ 
									std::cout<< "czytam zmienna" << endl;
									$$ = Variable($1);
								}
   | PIDENTIFIER LEFT_BRACE PIDENTIFIER RIGHT_BRACE  		{ 
									
								}
   | PIDENTIFIER LEFT_BRACE NUMBER RIGHT_BRACE 			{ 
									 
								}
   ;

%%


void yy::Parser::error( const location_type &l, const std::string &err_message )
{
   std::cerr << "Error: " << err_message << " at " << l << "\n";
}

