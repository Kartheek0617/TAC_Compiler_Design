#pragma once
#include <string>

struct ASTNode {
    virtual ~ASTNode() = default;
};

struct ExprNode : public ASTNode {
    int line;
    ExprNode(int l) : line(l) {}
    virtual std::string str() const = 0;
};

struct NumberNode : public ExprNode {
    int value;
    NumberNode(int val, int l) : ExprNode(l), value(val) {}
    std::string str() const override { return std::to_string(value); }
};

struct IdentifierNode : public ExprNode {
    std::string name;
    IdentifierNode(const std::string& n, int l) : ExprNode(l), name(n) {}
    std::string str() const override { return name; }
};

struct BinaryOpNode : public ExprNode {
    char op;
    ExprNode* left;
    ExprNode* right;
    
    BinaryOpNode(char o, ExprNode* l, ExprNode* r, int ln) 
        : ExprNode(ln), op(o), left(l), right(r) {}
        
    ~BinaryOpNode() { 
        delete left; 
        delete right; 
    }
    
    std::string str() const override { 
        return "(" + left->str() + " " + std::string(1, op) + " " + right->str() + ")"; 
    }
};

struct AssignNode : public ASTNode {
    std::string identifier;
    ExprNode* expression;
    int line;
    
    AssignNode(const std::string& id, ExprNode* expr, int l) 
        : identifier(id), expression(expr), line(l) {}
        
    ~AssignNode() { 
        delete expression; 
    }
};
