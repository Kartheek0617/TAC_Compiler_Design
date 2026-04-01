#include "semantic.h"
#include "error_handler.h"
#include <iostream>

void SemanticAnalyzer::checkExpression(ExprNode* node) {
    if (auto* idNode = dynamic_cast<IdentifierNode*>(node)) {
        if (!symbol_table.exists(idNode->name)) {
            throw SemanticError("Undeclared variable '" + idNode->name + "' used.", idNode->line);
        }
    } else if (auto* binOp = dynamic_cast<BinaryOpNode*>(node)) {
        checkExpression(binOp->left);
        checkExpression(binOp->right);
    }
}

void SemanticAnalyzer::analyze(const std::vector<AssignNode*>& statements) {
    for (auto* stmt : statements) {
        // First check the right-side expression variables are declared
        checkExpression(stmt->expression);
        // Then add the left-side identifier to the symbol table
        symbol_table.addVariable(stmt->identifier);
    }
}

void SemanticAnalyzer::printSymbolTable() const {
    std::cout << "\n--- 2. Symbol Table ---\n";
    for (const auto& pair : symbol_table.getTable()) {
        std::cout << "Var: " << pair.first << " | Type: INT\n";
    }
}
