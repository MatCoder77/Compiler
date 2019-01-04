#include "IfStatement.hpp"

IfStatement::IfStatement(ConditionPointer condition, CommandPointers commands) {
    this->condition = condition;
    this->commands = commands;
}

IfStatement::~IfStatement() {

}

void IfStatement::compile() {
    cout << "IF condition THEN commands ENDIF" << endl;
}