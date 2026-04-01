#include "target_code.h"
#include <iostream>

TargetCodeGenerator::TargetCodeGenerator() : regCount(1) {}

std::string TargetCodeGenerator::getReg() { 
    return "R" + std::to_string(regCount++); 
}

void TargetCodeGenerator::generate(const std::vector<TACInstruction>& tac) {
    std::cout << "\n--- Execution Order ---\n";
    int execOrder = 1;
    for (const auto& inst : tac) {
        if (inst.op == "=") {
            std::cout << "[" << execOrder++ << "] MOV " << inst.result << ", " << inst.arg1 << "\n";
        } else {
            std::string reg = getReg();
            std::cout << "[" << execOrder++ << "] LOAD " << reg << ", " << inst.arg1 << "\n";
            if (inst.op == "+") std::cout << "[" << execOrder++ << "] ADD ";
            else if (inst.op == "-") std::cout << "[" << execOrder++ << "] SUB ";
            else if (inst.op == "*") std::cout << "[" << execOrder++ << "] MUL ";
            else if (inst.op == "/") std::cout << "[" << execOrder++ << "] DIV ";
            std::cout << reg << ", " << inst.arg2 << "\n";
            std::cout << "[" << execOrder++ << "] STORE " << inst.result << ", " << reg << "\n";
        }
    }
}
