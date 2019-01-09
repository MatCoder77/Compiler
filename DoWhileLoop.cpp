#include "DoWhileLoop.hpp"

DoWhileLoop::DoWhileLoop(CommandPointers commands, ConditionPointer condition) {
    this->condition = condition;
    this->commands = commands;
}

void DoWhileLoop::compile() {
    ConditionBlock conditionBlock = condition->evaluateCondition(B, C);

    string IF_TRUE_LABEL = conditionBlock.getIfTrueLabel();
    string IF_FALSE_LABEL = conditionBlock.getIfFalseLabel();

    codeBlock.addLABEL(IF_TRUE_LABEL);
    for(auto& cmd : commands) {
        cmd->compile();
        codeBlock.append(cmd->getCodeBlock());
    }
    codeBlock.append(conditionBlock.getCodeBlock());
    codeBlock.addLABEL(IF_FALSE_LABEL);
}