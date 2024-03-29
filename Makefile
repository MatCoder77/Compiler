all: program

program: main.cpp ParsingDriver.cpp scanner.l parser.yy Command.cpp Variable.cpp Condition.cpp Expression.cpp WhileLoop.cpp Assignment.cpp Write.cpp DoWhileLoop.cpp ForLoop.cpp IfStatement.cpp IfElseStatement.cpp Read.cpp VariableManager.cpp CodeBlock.cpp
	flex scanner.l
	bison parser.yy
	g++ -Wall -Wno-sign-compare -g -o kompilator ParsingDriver.cpp parser.tab.cc lex.yy.cc main.cpp Command.cpp Variable.cpp Condition.cpp Expression.cpp WhileLoop.cpp Assignment.cpp Write.cpp DoWhileLoop.cpp ForLoop.cpp IfStatement.cpp IfElseStatement.cpp Read.cpp VariableManager.cpp CodeBlock.cpp -std=c++14

clean:
	rm parser.tab.cc parser.tab.hh location.hh position.hh stack.hh lex.yy.cc kompilator
