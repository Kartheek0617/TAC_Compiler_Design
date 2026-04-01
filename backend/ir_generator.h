#pragma once
#include "ast.h"
#include <vector>
#include <string>

struct TACInstruction {
    std::string op;
    std::string arg1;
    std::string arg2;
    std::string result;
    
    std::string toString() const;
};

class IRGenerator {
private:
    int tempCount;
    std::vector<TACInstruction> code;

    std::string generateExpr(ExprNode* node);

public:
    IRGenerator();
    void generate(const std::vector<AssignNode*>& statements);
    const std::vector<TACInstruction>& getCode() const;
    void printTAC() const;
};
