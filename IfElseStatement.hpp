//
// Created by mateusz on 04.01.19.
//

#ifndef COMPILER_IFELSESTATEMENT_HPP
#define COMPILER_IFELSESTATEMENT_HPP

#include "IfStatement.hpp"

class IfElseStatement : public  IfStatement{
public:
    IfElseStatement(ConditionPointer condition, CommandPointers commands, CommandPointers elseCommands);

    void compile();
private:
    CommandPointers elseCommands;
};


#endif //COMPILER_IFELSESTATEMENT_HPP
