//
// Created by mateusz on 04.01.19.
//

#ifndef COMPILER_FORLOOP_HPP
#define COMPILER_FORLOOP_HPP

#include "Command.hpp"
#include "Variable.hpp"

class ForLoop : public Command {
public:
    enum Type {
        TO,
        DOWNTO
    };
    ForLoop(Variable iterator, Variable rangeBegin, Type type, Variable rangeEnd, CommandPointers commands);

    void compile();
private:
    Variable iterator;
    Variable rangeBegin;
    Variable rangeEnd;
    Type type;
    CommandPointers commands;
};


#endif //COMPILER_FORLOOP_HPP
