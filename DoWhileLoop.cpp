#include "DoWhileLoop.hpp"

DoWhileLoop::DoWhileLoop(CommandPointers commands, ConditionPointer condition) {
    this->condition = condition;
    this->commands = commands;
}

void DoWhileLoop::compile() {

}