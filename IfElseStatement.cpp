#include "IfElseStatement.hpp"

IfElseStatement::IfElseStatement(ConditionPointer condition, CommandPointers commands, CommandPointers elseCommands)
: IfStatement(condition, commands){
    this->elseCommands = elseCommands;
}

void IfElseStatement::compile() {
    cout << "IF condition THEN commands ELSE commands ENDIF" << endl;
}