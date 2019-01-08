#include "IfStatement.hpp"

IfStatement::IfStatement(ConditionPointer condition, CommandPointers commands) {
    this->condition = condition;
    this->commands = commands;
}

IfStatement::~IfStatement() {

}

void IfStatement::compile() {
    ConditionBlock conditionBlock = condition->evaluateCondition(B, C);

    string IF_TRUE_LABEL = conditionBlock.getIfTrueLabel();
    string IF_FALSE_LABEL = conditionBlock.getIfFalseLabel();

    codeBlock = conditionBlock.getCodeBlock();
    codeBlock.addLABEL(IF_TRUE_LABEL);

    for(auto& cmd : commands) {
        cmd->compile();
        codeBlock.append(cmd->getCodeBlock());
    }

    codeBlock.addLABEL(IF_FALSE_LABEL);
}