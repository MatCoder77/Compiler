#include <iostream>

#include "ParsingDriver.hpp"

using namespace std;

int main(const int argc, const char* argv[]) {
    yy::ParsingDriver parsingDriver;
    parsingDriver.parse(argv[1]);
    parsingDriver.compile(argv[2]);
    //parsingDriver.print(cout);
}