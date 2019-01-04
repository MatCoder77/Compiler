#include "DoWhileLoop.hpp"

DoWhileLoop::DoWhileLoop(CommandPointers commands, ConditionPointer condition) {
    this->condition = condition;
    this->commands = commands;
}

void DoWhileLoop::compile() {
    cout << "DO commands WHILE condition ENDWHILE" << endl;
}