//
// Created by mateusz on 03.01.19.
//

#ifndef COMPILER_WRITE_HPP
#define COMPILER_WRITE_HPP

#include <iostream>
#include "Command.hpp"

using namespace std;

class Write : public Command {
public:
    Write();
    void compile();
};


#endif //COMPILER_WRITE_HPP
