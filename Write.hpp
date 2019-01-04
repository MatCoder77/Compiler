//
// Created by mateusz on 03.01.19.
//

#ifndef COMPILER_WRITE_HPP
#define COMPILER_WRITE_HPP

#include <iostream>
#include "Command.hpp"
#include "Variable.hpp"

using namespace std;

class Write : public Command {
public:
    Write(Variable variable);
    void compile();

private:
    Variable variable;
};


#endif //COMPILER_WRITE_HPP
