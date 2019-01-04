#include "WhileLoop.hpp"

WhileLoop::WhileLoop(ConditionPointer condition, CommandPointers commands) {
    this->condition = condition;
    this->commands = commands;
}

WhileLoop::~WhileLoop() {}

void WhileLoop::compile() {
    cout << "WHILE condition DO commands ENDWHILE" << endl;
}