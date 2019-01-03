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


#undef yylex
#define yylex scanner.yylex
}

%define api.value.type variant
%define parse.assert

%type <Variable> identifier
%type <Variable> value
%type <Expression> expression
%type <Condition> condition
%type <Command> command
%type <std::vector<Command>> commands

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
									std::cout<<"Parsing..." <<endl;
									
					  			}
   ;

declarations
   : %empty
   | declarations PIDENTIFIER SEMICOLON
   | declarations PIDENTIFIER LEFT_BRACE NUMBER COLON NUMBER RIGHT_BRACE SEMICOLON
   ;

commands
   : commands command 						{ 
									
								}
   | command 							{ 
									
								}
   ;

command
   : identifier ASSIGNMENT expression SEMICOLON 		{
         								
      								}
   | IF condition THEN commands ELSE commands ENDIF 		{

      								}
   | IF condition THEN commands ENDIF 				{

      								}
   | WHILE condition DO commands ENDWHILE 			{

      								}
   | DO commands WHILE condition ENDDO 				{

      								}
   | FOR PIDENTIFIER FROM value TO value DO commands ENDFOR 	{

      								}
   | FOR PIDENTIFIER FROM value DOWNTO value DO commands ENDFOR	{

      								}
   | READ identifier SEMICOLON 					{
         								
      								}
   | WRITE value SEMICOLON 					{
         								
      								}
   ;

expression
   : value 							{ 
									
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
									
								}
   | value LESSER_EQUAL value  					{ 
									 
								}
   | value GREATER_EQUAL value 					{ 
									
								}
   ;

value
   : NUMBER 							{ 
									
								}
   | identifier 						{ 
									
								}
   ;

identifier
   : PIDENTIFIER 						{ 
									
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

