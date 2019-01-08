//
// Created by mateusz on 02.01.19.
//

#ifndef COMPILER_COMMAND_HPP
#define COMPILER_COMMAND_HPP

#include <memory>
#include <vector>
#include <iostream>
#include "CodeBlock.hpp"

using  namespace std;

class Command {
public:
    Command() {}
    virtual ~Command(){}

    virtual void compile() = 0;

    CodeBlock getCodeBlock();

protected:
    CodeBlock codeBlock;
};

using CommandPointer = shared_ptr<Command>;
using CommandPointers = vector<CommandPointer>;

#endif //COMPILER_COMMAND_HPP
