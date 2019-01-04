//
// Created by mateusz on 04.01.19.
//

#ifndef COMPILER_READ_HPP
#define COMPILER_READ_HPP

#include "Command.hpp"
#include "Variable.hpp"

class Read : public  Command{
public:
    Read(Variable variable);

    void compile();

private:
    Variable variable;
};


#endif //COMPILER_READ_HPP
