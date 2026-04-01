#pragma once
#include <string>
#include <stdexcept>

// Base class for all compiler errors
class CompilerError : public std::runtime_error {
public:
    int line;
    CompilerError(const std::string& message, int lineNum) 
        : std::runtime_error(message), line(lineNum) {}
};

class LexicalError : public CompilerError {
public:
    LexicalError(const std::string& message, int lineNum) 
        : CompilerError("Lexical Error at line " + std::to_string(lineNum) + ": " + message, lineNum) {}
};

class SyntaxError : public CompilerError {
public:
    SyntaxError(const std::string& message, int lineNum) 
        : CompilerError("Syntax Error at line " + std::to_string(lineNum) + ": " + message, lineNum) {}
};

class SemanticError : public CompilerError {
public:
    SemanticError(const std::string& message, int lineNum) 
        : CompilerError("Semantic Error at line " + std::to_string(lineNum) + ": " + message, lineNum) {}
};
