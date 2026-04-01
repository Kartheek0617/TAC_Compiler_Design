#pragma once
#include <string>
#include <vector>

enum class TokenType {
    IDENTIFIER, NUMBER, ASSIGN, PLUS, MINUS, MUL, DIV, END_STATEMENT, END_OF_FILE, UNKNOWN
};

struct Token {
    TokenType type;
    std::string value;
    int line;
    
    std::string typeToString() const;
};

class Lexer {
private:
    std::string source;
    size_t pos;
    int line;

public:
    Lexer(const std::string& src);
    Token getNextToken();
    std::vector<Token> tokenize();
};
