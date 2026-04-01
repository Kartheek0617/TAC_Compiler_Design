#include "lexer.h"
#include "error_handler.h"
#include <cctype>

std::string Token::typeToString() const {
    switch (type) {
        case TokenType::IDENTIFIER: return "ID";
        case TokenType::NUMBER: return "NUM";
        case TokenType::ASSIGN: return "ASSIGN";
        case TokenType::PLUS: case TokenType::MINUS:
        case TokenType::MUL: case TokenType::DIV: return "OP";
        case TokenType::END_STATEMENT: return "NEWLINE";
        case TokenType::END_OF_FILE: return "EOF";
        default: return "UNKNOWN";
    }
}

Lexer::Lexer(const std::string& src) : source(src), pos(0), line(1) {}

Token Lexer::getNextToken() {
    while (pos < source.length()) {
        char current = source[pos];
        if (std::isspace(current)) {
            if (current == '\n') {
                line++;
                pos++;
                return {TokenType::END_STATEMENT, "\\n", line - 1};
            }
            pos++;
            continue;
        }

        if (std::isalpha(current)) {
            std::string id = "";
            while (pos < source.length() && std::isalnum(source[pos])) {
                id += source[pos++];
            }
            return {TokenType::IDENTIFIER, id, line};
        }

        if (std::isdigit(current)) {
            std::string num = "";
            while (pos < source.length() && std::isdigit(source[pos])) {
                num += source[pos++];
            }
            return {TokenType::NUMBER, num, line};
        }

        if (current == '=') { pos++; return {TokenType::ASSIGN, "=", line}; }
        if (current == '+') { pos++; return {TokenType::PLUS, "+", line}; }
        if (current == '-') { pos++; return {TokenType::MINUS, "-", line}; }
        if (current == '*') { pos++; return {TokenType::MUL, "*", line}; }
        if (current == '/') { pos++; return {TokenType::DIV, "/", line}; }

        pos++;
        return {TokenType::UNKNOWN, std::string(1, current), line};
    }
    return {TokenType::END_OF_FILE, "", line};
}

std::vector<Token> Lexer::tokenize() {
    std::vector<Token> tokens;
    Token t;
    do {
        t = getNextToken();
        if (t.type != TokenType::END_OF_FILE && t.type != TokenType::UNKNOWN) {
            tokens.push_back(t);
        } else if (t.type == TokenType::UNKNOWN) {
            throw LexicalError("Invalid Character '" + t.value + "'", t.line);
        }
    } while (t.type != TokenType::END_OF_FILE);
    tokens.push_back(t);
    return tokens;
}
