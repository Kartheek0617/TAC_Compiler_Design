#pragma once
#include "ast.h"
#include "lexer.h"
#include <vector>

class Parser {
private:
    std::vector<Token> tokens;
    size_t pos;

    Token currentToken() const;
    void advance();
    void expect(TokenType type);

    ExprNode* parsePrimary();
    ExprNode* parseTerm();
    ExprNode* parseExpression();

public:
    Parser(const std::vector<Token>& tokens);
    std::vector<AssignNode*> parse();
};
