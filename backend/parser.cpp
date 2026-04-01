#include "parser.h"
#include "error_handler.h"

Token Parser::currentToken() const {
    if (pos < tokens.size()) return tokens[pos];
    return {TokenType::END_OF_FILE, "", 0};
}

void Parser::advance() {
    if (pos < tokens.size()) pos++;
}

void Parser::expect(TokenType type) {
    if (currentToken().type == type) {
        advance();
    } else {
        throw SyntaxError("Unexpected token '" + currentToken().value + "'", currentToken().line);
    }
}

ExprNode* Parser::parsePrimary() {
    Token t = currentToken();
    if (t.type == TokenType::NUMBER) {
        advance();
        return new NumberNode(std::stoi(t.value), t.line);
    } else if (t.type == TokenType::IDENTIFIER) {
        advance();
        return new IdentifierNode(t.value, t.line);
    }
    throw SyntaxError("Expected number or identifier", t.line);
}

ExprNode* Parser::parseTerm() {
    ExprNode* left = parsePrimary();
    while (currentToken().type == TokenType::MUL || currentToken().type == TokenType::DIV) {
        char op = currentToken().value[0];
        int line = currentToken().line;
        advance();
        ExprNode* right = parsePrimary();
        left = new BinaryOpNode(op, left, right, line);
    }
    return left;
}

ExprNode* Parser::parseExpression() {
    ExprNode* left = parseTerm();
    while (currentToken().type == TokenType::PLUS || currentToken().type == TokenType::MINUS) {
        char op = currentToken().value[0];
        int line = currentToken().line;
        advance();
        ExprNode* right = parseTerm();
        left = new BinaryOpNode(op, left, right, line);
    }
    return left;
}

Parser::Parser(const std::vector<Token>& tokens) : tokens(tokens), pos(0) {}

std::vector<AssignNode*> Parser::parse() {
    std::vector<AssignNode*> statements;
    while (currentToken().type != TokenType::END_OF_FILE) {
        if (currentToken().type == TokenType::END_STATEMENT) {
            advance();
            continue;
        }
        if (currentToken().type == TokenType::IDENTIFIER) {
            std::string id = currentToken().value;
            int line = currentToken().line;
            advance();
            expect(TokenType::ASSIGN);
            ExprNode* expr = parseExpression();
            
            if (currentToken().type == TokenType::END_STATEMENT || currentToken().type == TokenType::END_OF_FILE) {
                if (currentToken().type == TokenType::END_STATEMENT) advance();
            } else {
                throw SyntaxError("Expected newline after statement", currentToken().line);
            }
            
            statements.push_back(new AssignNode(id, expr, line));
        } else {
            throw SyntaxError("Statement must start with an identifier", currentToken().line);
        }
    }
    return statements;
}
