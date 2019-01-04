//
// Created by mateusz on 04.01.19.
//

#ifndef COMPILER_DOWHILELOOP_HPP
#define COMPILER_DOWHILELOOP_HPP

#include "Command.hpp"
#include "Condition.hpp"

class DoWhileLoop : public Command {
public:
    DoWhileLoop(CommandPointers commands, ConditionPointer condition);

    void compile();
private:
    ConditionPointer condition;
    CommandPointers commands;
};


#endif //COMPILER_DOWHILELOOP_HPP
