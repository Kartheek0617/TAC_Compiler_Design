#pragma once
#include "ast.h"
#include "symbol_table.h"
#include <vector>

class SemanticAnalyzer {
private:
    SymbolTable symbol_table;

    void checkExpression(ExprNode* node);

public:
    void analyze(const std::vector<AssignNode*>& statements);
    void printSymbolTable() const;
};
