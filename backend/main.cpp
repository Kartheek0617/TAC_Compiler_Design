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
        
        // 2. Syntax Analysis
        Parser parser(tokens);
        vector<AssignNode*> ast = parser.parse();

        // 3. Semantic Analysis
        SemanticAnalyzer semanticAnalyzer;
        semanticAnalyzer.analyze(ast);

        // 4. IR Generation
        IRGenerator irGen;
        irGen.generate(ast);
        
        cout << "Output:\n";
        for (const auto& inst : irGen.getCode()) {
            if (inst.op == "=" && inst.arg1.find_first_not_of("0123456789") == string::npos && inst.arg2.empty()) {
                continue; 
            }
            cout << inst.toString() << "\n";
        }

        // 5. Code Optimization (Constant Folding)
        Optimizer optimizer;
        vector<TACInstruction> optimizedTac = optimizer.optimize(irGen.getCode());

        // 6. Target Code Generation
        cout << "\nInnovation Twist: Execution Order\n";
        TargetCodeGenerator codeGen;
        codeGen.generate(irGen.getCode());
        
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
