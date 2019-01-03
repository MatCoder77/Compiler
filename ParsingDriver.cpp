#include "ParsingDriver.hpp"

#include <fstream>
#include <sstream>

yy::ParsingDriver::~ParsingDriver() {
    delete(scanner);
    scanner = nullptr;
    delete(parser);
    parser = nullptr;
}

void yy::ParsingDriver::parse(const char *const filename) {
    ifstream file(filename);
    cout << "W parse" << endl;
    if (!file) {
        exit(EXIT_FAILURE);
    }
    scanner = new yy::Scanner(&file);
    parser = new yy::Parser(*scanner, *this);

    if(parser->parse() != 0)
    {
        std::cerr << "Parse failed!!\n";
    }
}

ostream& yy::ParsingDriver::print(std::ostream &stream) {
    stream << "Compilled succesfully!" << endl;
    return stream;
}