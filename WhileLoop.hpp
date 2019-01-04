//
// Created by mateusz on 03.01.19.
//

#ifndef COMPILER_WHILELOOP_HPP
#define COMPILER_WHILELOOP_HPP

#include <iostream>
#include "Command.hpp"
#include "Condition.hpp"

using namespace std;

class WhileLoop : public Command {
public:
    WhileLoop(ConditionPointer condition, CommandPointers commands);
    ~WhileLoop();

    void compile();
private:
    ConditionPointer condition;
    CommandPointers commands;
};


#endif //COMPILER_WHILELOOP_HPP
