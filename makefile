all: program

program: main.cpp ParsingDriver.cpp scanner.l parser.yy
	flex scanner.l
	bison parser.yy
	g++ -Wall -Wno-sign-compare -g -o compiler ParsingDriver.cpp grammar.cpp parser.tab.cc lex.yy.cc main.cpp -std=c++14

clean:
	rm parser.tab.cc parser.tab.hh location.hh position.hh stack.hh lex.yy.cc compiler
