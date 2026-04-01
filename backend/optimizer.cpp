#include "optimizer.h"
#include "error_handler.h"
#include <iostream>
#include <cctype>

bool Optimizer::isNumber(const std::string& s) const {
    for (char c : s) {
        if (!std::isdigit(c) && c != '-') return false;
    }
    return !s.empty();
}

std::vector<TACInstruction> Optimizer::optimize(const std::vector<TACInstruction>& code) {
    std::vector<TACInstruction> optimizedCode;
    for (const auto& inst : code) {
        if (inst.op != "=" && isNumber(inst.arg1) && isNumber(inst.arg2)) {
            int val1 = std::stoi(inst.arg1);
            int val2 = std::stoi(inst.arg2);
            int res = 0;
            if (inst.op == "+") res = val1 + val2;
            else if (inst.op == "-") res = val1 - val2;
            else if (inst.op == "*") res = val1 * val2;
            else if (inst.op == "/") {
                if (val2 == 0) throw CompilerError("Optimization Error: Division by zero", -1);
                res = val1 / val2; 
            }
            optimizedCode.push_back({"=", std::to_string(res), "", inst.result});
        } else {
            optimizedCode.push_back(inst);
        }
    }
    return optimizedCode;
}

void Optimizer::printOptimizedTAC(const std::vector<TACInstruction>& code) const {
    std::cout << "\n--- 4. Optimized TAC (Constant Folding) ---\n";
    for (const auto& inst : code) {
        std::cout << inst.toString() << "\n";
    }
}
