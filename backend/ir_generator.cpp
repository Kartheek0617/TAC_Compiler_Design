#include "ir_generator.h"
#include <iostream>

std::string TACInstruction::toString() const {
    if (op == "=") {
        return result + " = " + arg1;
    }
    return result + " = " + arg1 + " " + op + " " + arg2;
}

IRGenerator::IRGenerator() : tempCount(1) {}

std::string IRGenerator::generateExpr(ExprNode* node) {
    if (auto* numNode = dynamic_cast<NumberNode*>(node)) {
        return std::to_string(numNode->value);
    } else if (auto* idNode = dynamic_cast<IdentifierNode*>(node)) {
        return idNode->name;
    } else if (auto* binOp = dynamic_cast<BinaryOpNode*>(node)) {
        std::string left = generateExpr(binOp->left);
        std::string right = generateExpr(binOp->right);
        std::string temp = "t" + std::to_string(tempCount++);
        code.push_back({std::string(1, binOp->op), left, right, temp});
        return temp;
    }
    return "";
}

void IRGenerator::generate(const std::vector<AssignNode*>& statements) {
    for (auto* stmt : statements) {
        std::string exprResult = generateExpr(stmt->expression);
        code.push_back({"=", exprResult, "", stmt->identifier});
    }
}

const std::vector<TACInstruction>& IRGenerator::getCode() const { 
    return code; 
}

void IRGenerator::printTAC() const {
    std::cout << "\n--- 3. Intermediate Code (TAC) ---\n";
    for (const auto& inst : code) {
        std::cout << inst.toString() << "\n";
    }
}
