#include "ForLoop.hpp"

ForLoop::ForLoop(Variable iterator, Variable rangeBegin, ForLoop::Type type, Variable rangeEnd, CommandPointers commands) {
    this->iterator = iterator;
    this->rangeBegin = rangeBegin;
    this->rangeEnd = rangeEnd;
    this->type = type;
    this->commands = commands;
}

void ForLoop::compile() {
    cout << "FOR pidentifier FROM value ";
    if(type == TO) {
        cout << "TO ";
    }
    else {
        cout << "DOWNTO ";
    }
    cout << "value DO commands ENDFOR" << endl;
}