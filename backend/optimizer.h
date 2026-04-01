#pragma once
#include "ir_generator.h"
#include <vector>

class Optimizer {
private:
    bool isNumber(const std::string& s) const;

public:
    std::vector<TACInstruction> optimize(const std::vector<TACInstruction>& code);
    void printOptimizedTAC(const std::vector<TACInstruction>& code) const;
};
