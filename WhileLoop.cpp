#include "WhileLoop.hpp"

WhileLoop::WhileLoop(ConditionPointer condition, CommandPointers commands) {
    this->condition = condition;
    this->commands = commands;
}

WhileLoop::~WhileLoop() {}

void WhileLoop::compile() {
    ConditionBlock conditionBlock = condition->evaluateCondition(B, C);
    string WHILE_BEGIN_LABEL = CodeBlock::createUniqueLabel();
    cout << "WHILE_BEGIN_LABEL " << WHILE_BEGIN_LABEL << endl;
    string IF_TRUE_LABEL = conditionBlock.getIfTrueLabel();
    cout << "IF_TRUE_LABEL " << IF_TRUE_LABEL << endl;
    string IF_FALSE_LABEL = conditionBlock.getIfFalseLabel();
    cout << "IF_FALSE_LABEL " << IF_FALSE_LABEL << endl;
    CodeBlock conditionCode = conditionBlock.getCodeBlock();

    codeBlock.addLABEL(WHILE_BEGIN_LABEL);
    codeBlock.append(conditionCode);

    codeBlock.addLABEL(IF_TRUE_LABEL);
    for(auto& cmd : commands) {
        cmd->compile();
        codeBlock.append(cmd->getCodeBlock());
    }
    codeBlock.addJUMP(WHILE_BEGIN_LABEL);
    codeBlock.addLABEL(IF_FALSE_LABEL);
}