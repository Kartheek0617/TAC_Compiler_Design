#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "error_handler.h"
#include "lexer.h"
#include "parser.h"
#include "semantic.h"
#include "ir_generator.h"
#include "optimizer.h"
#include "target_code.h"

using namespace std;

void runCompiler(const string& sourceCode) {
    try {
        // 1. Lexical Analysis
        Lexer lexer(sourceCode);
        vector<Token> tokens = lexer.tokenize();
        
        cout << "\n--- 1. Tokens ---\n";
        for (const auto& t : tokens) {
            if (t.type != TokenType::END_OF_FILE) {
                cout << "[" << t.typeToString() << ": " << t.value << "] ";
            }
        }
        cout << "\n";

        // 2. Syntax Analysis
        Parser parser(tokens);
        vector<AssignNode*> ast = parser.parse();

        // 3. Semantic Analysis
        SemanticAnalyzer semanticAnalyzer;
        semanticAnalyzer.analyze(ast);
        cout << "\n--- 3. Symbol Table ---\n";
        semanticAnalyzer.printSymbolTable();

        // 4. IR Generation
        IRGenerator irGen;
        irGen.generate(ast);
        cout << "\n--- 4. Intermediate Representation (TAC) ---\n";
        irGen.printTAC();

        // 5. Code Optimization (Constant Folding)
        Optimizer optimizer;
        vector<TACInstruction> optimizedTac = optimizer.optimize(irGen.getCode());
        cout << "\n--- 5. Optimized TAC ---\n";
        optimizer.printOptimizedTAC(optimizedTac);

        // 6. Target Code Generation
        TargetCodeGenerator codeGen;
        cout << "\n--- 6. Target Code ---\n";
        codeGen.generate(optimizedTac);
        
        // Cleanup AST
        for (auto* node : ast) delete node;
        
    } catch (const CompilerError& e) {
        cerr << "\n>>> " << e.what() << " <<<\n";
    } catch (const exception& e) {
        cerr << "\n>>> ERROR: " << e.what() << " <<<\n";
    }
}

int main(int argc, char* argv[]) {
    string sourceCode;
    
    if (argc > 1) {
        ifstream file(argv[1]);
        if (!file.is_open()) {
            cerr << "Could not open file: " << argv[1] << "\n";
            return 1;
        }
        stringstream buffer;
        buffer << file.rdbuf();
        sourceCode = buffer.str();
    } else {
        string line;
        while (getline(cin, line)) {
            sourceCode += line + "\n";
        }
    }

    if (sourceCode.empty()) {
        cout << "No source code provided.\n";
        return 0;
    }

    runCompiler(sourceCode);
    return 0;
}
