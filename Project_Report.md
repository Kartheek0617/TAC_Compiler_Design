# Project Report: Full-Stack Mini-Compiler Web IDE

## 1. Introduction
The **Mini-Compiler Web IDE** is a modern, full-stack application designed to demonstrate the fundamental phases of a real-world compiler architecture. The system processes a simple expression-based assignment language and traces the compilation steps visually back to a browser-based user interface. This project bridges systems programming concepts with modern web development paradigms.

## 2. Objective
The primary objective of this project is to implement a strict 6-phase compiler that executes sequentially while providing real-time feedback through a visual IDE interface. It parses string-based algebraic code, tracks mathematical and semantic logic, optimizes instructions at compile-time, and generates target pseudo-assembly.

## 3. System Architecture
The application is separated into three highly cohesive layers:

*   **Frontend (Browser UI)**: Built using pure HTML, CSS, and Vanilla JavaScript. It serves as the code editor where users can input instructions directly.
*   **Web Server (Python Flask)**: Acts as the intermediary API bridge. It accepts POST requests containing user-written code from the frontend, executes the target C++ binary, monitors timeouts or execution failures, and passes the standard output text back to the frontend.
*   **Compiler Engine (C++)**: The low-level backend compiled into an executable (`compiler.exe`). It sequentially drives the compilation pipeline and yields internal state metadata via the terminal.

## 4. Compiler Phases Implementations
The core compiler is fully modularized and performs the following operations during execution:

### 4.1. Lexical Analysis (Scanner)
Implemented in `lexer.cpp`. This phase consumes the raw source text character by character, filtering whitespace and newlines, and tokenizes strings into valid identifiers, constants, and operators representing the language rules. Unknown characters are flagged to halt compilation.

### 4.2. Syntax Analysis (Parser)
Implemented in `parser.cpp`. Operating on the generated tokens, this phase evaluates grammar using recursive descent logic to construct an Abstract Syntax Tree (AST). It groups arithmetic constraints based on operator precedence rules.

### 4.3. Semantic Analysis
Implemented in `semantic.cpp`. Traversing the generated AST, the compiler utilizes an `unordered_map` as a Symbol Table. The analyzer mandates context-sensitive policies, most prominently checking that all variables used in mathematical expressions have been previously declared.

### 4.4. Intermediate Code Generation
Implemented in `ir_generator.cpp`. This phase flattens the multidimensional AST into sequence-driven Three Address Code (TAC). For arithmetic operations, it continuously designates temporary registers (`t1`, `t2`, etc.) to store sequential mid-calculation results.

### 4.5. Code Optimization (Constant Folding)
Implemented in `optimizer.cpp`. The compiler statically analyzes the established TAC stream. It actively identifies arithmetic assignments where both operands are constants (e.g., `5 + 5` instead of `a + b`). It evaluates these mathematically before runtime and alters the underlying TAC to be a direct numerical constant assignment (`10`), significantly reducing physical runtime overhead.

### 4.6. Target Code Generation
Implemented in `target_code.cpp`. The final logical step resolves the optimized TAC blocks into primitive sequential assembly language, executing generalized `LOAD`, `STORE`, `ADD`, `MUL`, and `DIV` expressions based on simulated registers mapping the instructions sequentially.

## 5. Technology Stack
*   **Systems Programming**: C++ (Standard Library, Object-Oriented paradigms)
*   **Web Server**: Python 3, Flask Micro-framework, Subprocess Management
*   **Frontend Technologies**: HTML5, CSS3, JavaScript (Fetch API / Promises) 

## 6. Directory Structure
```text
Compiler_Design/
├── backend/            # Modular C++ compiler headers and sources
│   ├── lexer.h/.cpp, parser.h/.cpp, etc.
│   └── compiler.exe    # The compiled engine binary
├── frontend/           # The User Interface 
│   ├── index.html
│   ├── style.css
│   └── script.js
├── server/             # The REST API bridge
│   └── app.py
├── Project_Report.md   # This documentation file
└── README.md           # Instructions on compilation & initialization
```

## 7. Conclusion
This project successfully marries complex theoretical computer science concepts with accessible, modern web technologies. By strictly enforcing separation of concerns between analytical compilation and web visualization, the Mini-Compiler Web IDE provides both algorithmic integrity and excellent user accessibility.
