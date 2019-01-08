//
// Created by mateusz on 07.01.19.
//

#ifndef COMPILER_CODEBLOCK_HPP
#define COMPILER_CODEBLOCK_HPP

#include <vector>
#include <string>

using namespace std;

enum Register{A, B, C, D, E, F, G, H};

class CodeBlock {
public:
    void addGET(Register reg);
    void addPUT(Register reg);
    void addLOAD(Register reg);
    void addSTORE(Register reg);
    void addCOPY(Register to, Register from);
    void addADD(Register r1, Register r2);
    void addSUB(Register r1, Register r2);
    void addHALF(Register reg);
    void addINC(Register reg);
    void addDEC(Register reg);
    void addJUMP(string label);
    void addJZERO(Register reg, string label);
    void addJODD(Register reg, string label);
    void addHALT();
    void addLABEL(string label);
    string toString(Register reg);
    static string createUniqueLabel();
    void append(CodeBlock block);
    vector<string>& getCode();
private:
    static int labelCounter;
    vector<string> codeBlock;
};


#endif //COMPILER_CODEBLOCK_HPP
