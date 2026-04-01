# Full-Stack Mini-Compiler Web IDE

A professional, full-stack browser-based mini-compiler project. 

## Project Structure
```text
mini-compiler-web/
├── backend/        (C++ compiler modules)
│   ├── main.cpp, lexer.cpp, parser.cpp ...
│   └── compiler.exe
├── server/         (Python Flask backend API)
│   └── app.py
├── frontend/       (Web UI - HTML/CSS/JS)
│   ├── index.html
│   ├── style.css
│   └── script.js
└── README.md
```

## Compiler Phases
The backend implements a strict 6-phase compiler architecture:
1. **Lexical Analysis (`lexer.cpp`)**: Tokenizes input strings.
2. **Syntax Analysis (`parser.cpp`)**: Validates grammar and builds an AST.
3. **Semantic Analysis (`semantic.cpp`)**: Evaluates symbols and flags undeclared variables.
4. **Intermediate Code Generation (`ir_generator.cpp`)**: Converts AST to Three-Address Code (TAC).
5. **Code Optimization (`optimizer.cpp`)**: Performs compile-time constant folding.
6. **Target Code Generation (`target_code.cpp`)**: Outputs pseudo-assembly showing Execution Order tracking.

## How to Run

### 1. Compile the C++ Backend
First, you must compile the C++ engine so the Python server can execute it. Open your terminal in the root folder:
```bash
cd backend
g++ main.cpp lexer.cpp parser.cpp semantic.cpp ir_generator.cpp optimizer.cpp target_code.cpp -o compiler.exe
cd ..
```

### 2. Start the Flask Server
Ensure you have Python and Flask installed (`pip install flask`). 
```bash
cd server
python app.py
```

### 3. Open the Frontend
The Flask server automatically serves the frontend natively! Open your browser and navigate to:
```text
http://localhost:5000/
```

## Sample Input / Output
**Input (in browser editor):**
```text
a = 10
b = a + 5
c = b * 2
```

**Output:**
The backend will trace everything back to the web UI:
- Tokens: `[ID: a] [ASSIGN: =] [NUM: 10] ...`
- Symbol Table tracking assignments
- TAC Intermediate Representations
- Optimized Constant Folding
- Finally, the pseudo-assembly execution:
  `[1] LOAD R1, a`
  `[2] ADD R1, 5`
  ...
