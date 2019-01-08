//
// Created by mateusz on 07.01.19.
//

#include "CodeBlock.hpp"

int CodeBlock::labelCounter = 0;

string CodeBlock::toString(Register reg) {
    switch (reg) {
        case A:
            return "A";
        case B:
            return "B";
        case C:
            return "C";
        case D:
            return "D";
        case E:
            return "E";
        case F:
            return "F";
        case G:
            return "G";
        case H:
            return "H";
        default:
            return "ERROR";
    }
}

void CodeBlock::addGET(Register reg) {
    string cmd = "GET ";
    cmd += toString(reg);
    codeBlock.push_back(cmd);
}

void CodeBlock::addPUT(Register reg) {
    string cmd = "PUT ";
    cmd += toString(reg);
    codeBlock.push_back(cmd);
}

void CodeBlock::addLOAD(Register reg) {
    string cmd = "LOAD ";
    cmd += toString(reg);
    codeBlock.push_back(cmd);
}

void CodeBlock::addSTORE(Register reg) {
    string cmd = "STORE ";
    cmd += toString(reg);
    codeBlock.push_back(cmd);
}

void CodeBlock::addCOPY(Register to, Register from) {
    string cmd = "COPY ";
    cmd += toString(to);
    cmd += " ";
    cmd += toString(from);
    codeBlock.push_back(cmd);
}

void CodeBlock::addADD(Register r1, Register r2) {
    string cmd = "ADD ";
    cmd += toString(r1);
    cmd += " ";
    cmd += toString(r2);
    codeBlock.push_back(cmd);
}

void CodeBlock::addSUB(Register r1, Register r2) {
    string cmd = "SUB ";
    cmd += toString(r1);
    cmd += " ";
    cmd += toString(r2);
    codeBlock.push_back(cmd);
}

void CodeBlock::addHALF(Register reg) {
    string cmd = "HALF ";
    cmd += toString(reg);
    codeBlock.push_back(cmd);
}

void CodeBlock::addINC(Register reg) {
    string cmd = "INC ";
    cmd += toString(reg);
    codeBlock.push_back(cmd);
}

void CodeBlock::addDEC(Register reg) {
    string cmd = "DEC ";
    cmd += toString(reg);
    codeBlock.push_back(cmd);
}

void CodeBlock::addJUMP(string label) {
    string cmd = "JUMP $";
    cmd += label;
    codeBlock.push_back(cmd);
}

void CodeBlock::addJZERO(Register reg, string label) {
    string cmd = "JZERO ";
    cmd += toString(reg);
    cmd += " $";
    cmd += label;
    codeBlock.push_back(cmd);
}

void CodeBlock::addJODD(Register reg, string label) {
    string cmd = "JODD ";
    cmd += toString(reg);
    cmd += " $";
    cmd += label;
    codeBlock.push_back(cmd);
}

void CodeBlock::addHALT() {
    string cmd = "HALT";
    codeBlock.push_back(cmd);
}

void CodeBlock::addLABEL(string label) {
    string cmd = "#";
    cmd += label;
    codeBlock.push_back(cmd);
}

void CodeBlock::append(CodeBlock block) {
    vector<string> inner = block.getCode();
    codeBlock.insert(codeBlock.end(), inner.begin(), inner.end());
}

string CodeBlock::createUniqueLabel() {
    return to_string(labelCounter++);
}

vector<string>& CodeBlock::getCode() {
    return codeBlock;
}