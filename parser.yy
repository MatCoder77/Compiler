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

      								}
   | IF condition THEN commands ENDIF 				{

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

      								}
   | READ identifier SEMICOLON 					{
         								
      								}
   | WRITE value SEMICOLON 					{
									cout << "Czytam WRITE" << endl;
         								$$ = std::make_shared<Write>();	
      								}
   ;

expression
   : value 							{ 
									$$ = Expression($1);
								}
   | value ADD value 						{ 
									
								}
   | value SUB value 						{ 
									
								}
   | value MUL value 						{ 
									 
								}
   | value DIV value 						{ 
									
								}
   | value MOD value 						{ 
									
								}
   ;

condition
   : value EQUAL value  					{ 
									
								}
   | value NOT_EQUAL value 					{ 
									 
								}
   | value LESSER value   					{ 
									
								}
   | value GREATER value  					{ 
									cout << "czytam warunek" << endl;
									$$ = std::make_shared<Condition>(Condition::Type::GREATER, $1, $3);
								}
   | value LESSER_EQUAL value  					{ 
									 
								}
   | value GREATER_EQUAL value 					{ 
									
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
									std::cout<<"czytam zmienna" << endl;
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

