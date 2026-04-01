#pragma once
#include "ir_generator.h"
#include <vector>
#include <string>

class TargetCodeGenerator {
private:
    int regCount;
    std::string getReg();
    
public:
    TargetCodeGenerator();
    void generate(const std::vector<TACInstruction>& tac);
};
