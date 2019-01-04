//
// Created by mateusz on 04.01.19.
//

#ifndef COMPILER_IFSTATEMENT_HPP
#define COMPILER_IFSTATEMENT_HPP

#include "Command.hpp"
#include "Condition.hpp"

class IfStatement : public Command {
public:
    IfStatement(ConditionPointer condition, CommandPointers commands);
    virtual ~IfStatement();
    void compile();

protected:
    ConditionPointer  condition;
    CommandPointers commands;
};


#endif //COMPILER_IFSTATEMENT_HPP
