#include "IfElseStatement.hpp"

IfElseStatement::IfElseStatement(ConditionPointer condition, CommandPointers commands, CommandPointers elseCommands)
: IfStatement(condition, commands){
    this->elseCommands = elseCommands;
}

void IfElseStatement::compile() {
    ConditionBlock conditionBlock = condition->evaluateCondition(B, C);

    string IF_TRUE_LABEL = conditionBlock.getIfTrueLabel();
    string IF_FALSE_LABEL = conditionBlock.getIfFalseLabel();
    string END = CodeBlock::createUniqueLabel();

    codeBlock = conditionBlock.getCodeBlock();

    codeBlock.addLABEL(IF_TRUE_LABEL);
    for(auto& cmd : commands) {
        cmd->compile();
        codeBlock.append(cmd->getCodeBlock());
    }
    codeBlock.addJUMP(END);

    codeBlock.addLABEL(IF_FALSE_LABEL);
    for(auto& cmd : elseCommands) {
        cmd->compile();
        codeBlock.append(cmd->getCodeBlock());
    }
    codeBlock.addLABEL(END);
}