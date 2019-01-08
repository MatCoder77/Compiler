%skeleton "lalr1.cc"
%require  "3.0"
%debug
%defines
%define parser_class_name 	{ Parser }
%parse-param 			{ Scanner& scanner  }
%parse-param 			{ ParsingDriver& parsingDriver  }
%locations

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
   #include "CodeBlock.hpp"
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
   #include "CodeBlock.hpp"

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




%define parse.error verbose

%%

program
   : DECLARE declarations IN commands END 			{ 
									std::cout<<"Parsing..." << endl;
									parsingDriver.setCommands($4);
					  			}
   ;

declarations
   : %empty
   | declarations PIDENTIFIER SEMICOLON				{
									Variable variableToDeclare($2);
									parsingDriver.declare(variableToDeclare);
									cout << "Deklaracja zmiennej " << variableToDeclare.getIdentifier() << endl;
									cout << "Przydzielony adres: " << variableToDeclare.getAddress() << endl;
								}
   | declarations PIDENTIFIER LEFT_BRACE NUMBER COLON NUMBER RIGHT_BRACE SEMICOLON {
									Variable firstIndex(std::stoll($4));
									Variable lastIndex(std::stoll($6));
									Variable array($2, firstIndex.getValue(), lastIndex.getValue());
									string errorMessage = "Invalid declaration of array ";
									errorMessage += array.getIdentifier();
									errorMessage += ", last index is smaller than first";
									parsingDriver.checkCondition(array.getLastIndex() >= array.getFirstIndex(), errorMessage);
									parsingDriver.declare(array);
									cout << "Deklaracja tablicy " << array.getIdentifier() << "(" << array.getFirstIndex() << ":" << array.getLastIndex() << ")" << endl;
									cout << "Przydzielony adres: " << array.getAddress() << endl;
								}
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
									Variable& targetVariable = $1;
									string errorMessage = "Illegal assignment to iterator ";
									errorMessage += targetVariable.getIdentifier();
									parsingDriver.checkCondition(!targetVariable.isDeclaredAsIterator(), errorMessage);
									errorMessage = "Illegal assignment to array ";
									errorMessage += targetVariable.getIdentifier();
									parsingDriver.checkCondition(targetVariable.getType() != Variable::Type::ARRAY, errorMessage);
         								$$ = std::make_shared<Assignment>(targetVariable, $3);
									parsingDriver.markVariableAsInitialized(targetVariable.getIdentifier());
									cout << "Przypisanie do zmiennej " << targetVariable.getIdentifier() << endl;
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
   | FOR PIDENTIFIER FROM value TO value			{
									Variable iterator($2, true);
									parsingDriver.declare(iterator);
									cout << "Zadeklarowano iterator " << iterator.getIdentifier() << endl;
									cout << "Przydzielony adres: " << iterator.getAddress() << endl;
									cout << "Tworzenie pętli FOR o iteratorze " << iterator.getIdentifier() << endl;
								}
     DO commands ENDFOR 					{
									Variable iter = parsingDriver.getDeclaredVariable($2);
									$$ = make_shared<ForLoop>(iter, $4, ForLoop::Type::TO, $6, $9);
									cout << "Utworzono pętlę FOR o iteratorze " << iter.getIdentifier() << endl;
									parsingDriver.undeclare(iter);
      								}
   | FOR PIDENTIFIER FROM value DOWNTO value 			{
									Variable iterator($2, true);
									parsingDriver.declare(iterator);
									cout << "Zadeklarowano iterator " << iterator.getIdentifier() << endl;
									cout << "Przydzielony adres: " << iterator.getAddress() << endl;
									cout << "Tworzenie pętli FOR DOWNTO o iteratorze " << iterator.getIdentifier() << endl;
								}
     DO commands ENDFOR						{
									Variable iter = parsingDriver.getDeclaredVariable($2);
									$$ = make_shared<ForLoop>(iter, $4, ForLoop::Type::DOWNTO, $6, $9);
									cout << "Utworzono pętlę FOR o iteratorze " << iter.getIdentifier() << endl;
									parsingDriver.undeclare(iter);
      								}
   | READ identifier SEMICOLON 					{
         								Variable& variable = $2;
									$$ = make_shared<Read>(variable);
									parsingDriver.markVariableAsInitialized(variable.getIdentifier());
									cout << "Wczytano wartość do zmiennej " << variable.getIdentifier() << endl;
									
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
									Variable& variable = $1;
									string errorMessage = "Use of uninitialized variable ";
									errorMessage += variable.getIdentifier();
									parsingDriver.checkCondition(variable.isVariableInitialized(), errorMessage);
									$$ = $1;
								}
   ;

identifier
   : PIDENTIFIER 						{ 
									Variable variable = parsingDriver.getDeclaredVariable($1);
									string errorMessage = "Array connot be used in this context";
									parsingDriver.checkCondition(variable.getType() != Variable::Type::ARRAY, errorMessage);
									std::cout<< "Użycie zmiennej " <<  variable.getIdentifier() << endl;
									$$ = variable;									
								}
   | PIDENTIFIER LEFT_BRACE PIDENTIFIER RIGHT_BRACE  		{ 
									Variable variable = parsingDriver.getDeclaredVariable($1);
									string errorMessage = "Variable ";
									errorMessage += variable.getIdentifier();
									errorMessage += " is not an array";
									parsingDriver.checkCondition(variable.getType() == Variable::Type::ARRAY, errorMessage);
									Variable index = parsingDriver.getDeclaredVariable($3);
									errorMessage = "Variable ";
									errorMessage += index.getIdentifier();
									errorMessage += " is uninitialzed";
									parsingDriver.checkCondition(index.isVariableInitialized(), errorMessage);
									Variable arrayElement = parsingDriver.getElementFromDeclaredArray(variable.getIdentifier(), index);
									cout << "Odwołanie do elementu " << arrayElement.getIndexInOwningArrayIdentifier() << " tablicy " << arrayElement.getIdentifier() << endl;
									$$ = arrayElement;
								}
   | PIDENTIFIER LEFT_BRACE NUMBER RIGHT_BRACE 			{
									Variable variable = parsingDriver.getDeclaredVariable($1);
									string errorMessage = "Variable ";
									errorMessage += variable.getIdentifier();
									errorMessage += " is not an array";
									parsingDriver.checkCondition(variable.getType() == Variable::Type::ARRAY, errorMessage);
									long long index = stoll($3);
									errorMessage = "Index of array ";
									errorMessage += variable.getIdentifier();
									errorMessage += " out of bounds";
									parsingDriver.checkCondition(index >= variable.getFirstIndex() && index <= variable.getLastIndex(), errorMessage);
									Variable arrayElement = parsingDriver.getElementFromDeclaredArray(variable.getIdentifier(), index);
									cout << "Odwołanie do elementu " << arrayElement.getIndexInOwningArray() << " tablicy " << arrayElement.getIdentifier() << endl;
									cout << "Adres elementu: " << arrayElement.getAddress() << endl;
									$$ = arrayElement;
								}
   ;

%%


void yy::Parser::error( const location_type &l, const std::string &err_message )
{
    std::cerr << "Error: " << err_message << " at " << l << "\n";
    exit(1);
}

