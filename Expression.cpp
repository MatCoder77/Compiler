#include "Expression.hpp"

Expression::Expression() {}

Expression::Expression(Variable variable) {
    this->type = VARIABLE;
    this->leftHandSide = variable;
}

Expression::Expression(Expression::Type type, Variable leftHandSide, Variable rightHandSide) {
    this->type = type;
    this->leftHandSide = leftHandSide;
    this->rightHandSide = rightHandSide;
}

void Expression::compile() {
    cout << "expression";
}

Variable Expression::getLeftHandSide() {
    return leftHandSide;
}

Variable Expression::getRightHandSide() {
    return rightHandSide;
}

Expression::Type Expression::getType() {
    return type;
}

string Expression::getTypeString() {
    switch (type) {
        case VARIABLE:
            return "";
        case ADDITION:
            return "+";
        case MULTIPLICATION:
            return "*";
        case SUBTRACTION:
            return "-";
        case DIVISION:
            return "/";
        case MODULO:
            return "%";
    }
    return "ERROR";
}

CodeBlock Expression::loadResultToRegister(Register reg) {
    CodeBlock codeBlock;
    switch (type) {
        case VARIABLE: {
            codeBlock = leftHandSide.loadValueToRegister(reg);
            break;
        }
        case ADDITION: {
            codeBlock = leftHandSide.loadValueToRegister(B);
            codeBlock.append(rightHandSide.loadValueToRegister(C));
            codeBlock.addADD(B, C);
            if(reg != B) {
                codeBlock.addCOPY(reg, B);
            }
            break;
        }
        case MULTIPLICATION: {
            string C_GREATER_LABEL = CodeBlock::createUniqueLabel();
            string LOOP_1_LABEL = CodeBlock::createUniqueLabel();
            string LOOP_2_LABEL = CodeBlock::createUniqueLabel();
            string END_LABEL = CodeBlock::createUniqueLabel();

            codeBlock.addSUB(D, D);
            codeBlock.append(leftHandSide.loadValueToRegister(B));
            codeBlock.addJZERO(B, END_LABEL);
            codeBlock.append(rightHandSide.loadValueToRegister(C));
            codeBlock.addJZERO(C, END_LABEL);
            codeBlock.addCOPY(E, B);
            codeBlock.addSUB(E, C);
            codeBlock.addJZERO(E, C_GREATER_LABEL);
            codeBlock.addLABEL(LOOP_1_LABEL);
            codeBlock.addJZERO(C, END_LABEL);
            codeBlock.addADD(D, B);
            codeBlock.addDEC(C);
            codeBlock.addJUMP(LOOP_1_LABEL);
            codeBlock.addLABEL(LOOP_2_LABEL);
            codeBlock.addJZERO(B, END_LABEL);
            codeBlock.addLABEL(C_GREATER_LABEL);
            codeBlock.addADD(D, C);
            codeBlock.addDEC(B);
            codeBlock.addJUMP(LOOP_2_LABEL);
            codeBlock.addLABEL(END_LABEL);
            if(reg != D) {
                codeBlock.addCOPY(reg, D);
            }

            break;
        }

        case SUBTRACTION: {
            codeBlock = leftHandSide.loadValueToRegister(B);
            codeBlock.append(rightHandSide.loadValueToRegister(C));
            codeBlock.addSUB(B, C);
            if(reg != B) {
                codeBlock.addCOPY(reg, B);
            }
            break;
        }

        case DIVISION: {
            string LABEL_1 = CodeBlock::createUniqueLabel();
            string LABEL_2 = CodeBlock::createUniqueLabel();
            string LABEL_3 = CodeBlock::createUniqueLabel();
            string LABEL_4 = CodeBlock::createUniqueLabel();
            string LABEL_5 = CodeBlock::createUniqueLabel();
            string LABEL_6 = CodeBlock::createUniqueLabel();
            string LABEL_7 = CodeBlock::createUniqueLabel();
            string LABEL_8 = CodeBlock::createUniqueLabel();

            codeBlock = rightHandSide.loadValueToRegister(C);
            codeBlock.addJZERO(C, LABEL_7);
            codeBlock.addJUMP(LABEL_8);
            codeBlock.addLABEL(LABEL_7);
            codeBlock.addSUB(D, D);
            codeBlock.addJUMP(LABEL_3);
            codeBlock.addLABEL(LABEL_8);
            codeBlock.append(leftHandSide.loadValueToRegister(B));
            codeBlock.addSUB(E,E);         //0
            codeBlock.addLABEL(LABEL_1);
            codeBlock.addCOPY(F, B);      //1
            codeBlock.addINC(F);          //2
            codeBlock.addSUB(F, C);       //3
            codeBlock.addJZERO(F, LABEL_2); //4
            codeBlock.addINC(E);     //5
            codeBlock.addADD(C, C);  //6
            codeBlock.addJUMP(LABEL_1);  //7
            codeBlock.addLABEL(LABEL_2);
            codeBlock.addHALF(C);   //8
            codeBlock.addSUB(D, D); //9
            codeBlock.addLABEL(LABEL_6);
            codeBlock.addJZERO(E, LABEL_3);  //10
            codeBlock.addCOPY(F, B);  //11
            codeBlock.addINC(F);   //12
            codeBlock.addSUB(F, C); //13
            codeBlock.addJZERO(F, LABEL_4);  //14
            codeBlock.addSUB(B, C); //15
            codeBlock.addADD(D, D);  //16
            codeBlock.addINC(D);   //17
            codeBlock.addJUMP(LABEL_5);  //18
            codeBlock.addLABEL(LABEL_4);
            codeBlock.addADD(D, D);  //19
            codeBlock.addLABEL(LABEL_5);
            codeBlock.addHALF(C);   //20
            codeBlock.addDEC(E);   //21
            codeBlock.addJUMP(LABEL_6); //22
            codeBlock.addLABEL(LABEL_3); //23
            if(reg != D) {
                codeBlock.addCOPY(reg, D);
            }
            break;
        }

        case MODULO: {
            string LABEL_1 = CodeBlock::createUniqueLabel();
            string LABEL_2 = CodeBlock::createUniqueLabel();
            string LABEL_3 = CodeBlock::createUniqueLabel();
            string LABEL_4 = CodeBlock::createUniqueLabel();
            string LABEL_5 = CodeBlock::createUniqueLabel();
            string LABEL_6 = CodeBlock::createUniqueLabel();
            string LABEL_7 = CodeBlock::createUniqueLabel();
            string LABEL_8 = CodeBlock::createUniqueLabel();

            codeBlock = rightHandSide.loadValueToRegister(C);
            codeBlock.addJZERO(C, LABEL_7);
            codeBlock.addJUMP(LABEL_8);
            codeBlock.addLABEL(LABEL_7);
            codeBlock.addSUB(B, B);
            codeBlock.addJUMP(LABEL_3);
            codeBlock.addLABEL(LABEL_8);
            codeBlock.append(leftHandSide.loadValueToRegister(B));
            codeBlock.addSUB(E,E);         //0
            codeBlock.addLABEL(LABEL_1);
            codeBlock.addCOPY(F, B);      //1
            codeBlock.addINC(F);          //2
            codeBlock.addSUB(F, C);       //3
            codeBlock.addJZERO(F, LABEL_2); //4
            codeBlock.addINC(E);     //5
            codeBlock.addADD(C, C);  //6
            codeBlock.addJUMP(LABEL_1);  //7
            codeBlock.addLABEL(LABEL_2);
            codeBlock.addHALF(C);   //8
            codeBlock.addSUB(D, D); //9
            codeBlock.addLABEL(LABEL_6);
            codeBlock.addJZERO(E, LABEL_3);  //10
            codeBlock.addCOPY(F, B);  //11
            codeBlock.addINC(F);   //12
            codeBlock.addSUB(F, C); //13
            codeBlock.addJZERO(F, LABEL_4);  //14
            codeBlock.addSUB(B, C); //15
            codeBlock.addADD(D, D);  //16
            codeBlock.addINC(D);   //17
            codeBlock.addJUMP(LABEL_5);  //18
            codeBlock.addLABEL(LABEL_4);
            codeBlock.addADD(D, D);  //19
            codeBlock.addLABEL(LABEL_5);
            codeBlock.addHALF(C);   //20
            codeBlock.addDEC(E);   //21
            codeBlock.addJUMP(LABEL_6); //22
            codeBlock.addLABEL(LABEL_3); //23
            if(reg != B) {
                codeBlock.addCOPY(reg, B);
            }
            break;
        }
    }
    return codeBlock;
}

string Expression::getExpressionString() {
    return "TODO";
}