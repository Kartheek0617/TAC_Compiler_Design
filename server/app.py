from flask import Flask, request, jsonify, render_template, send_from_directory
import subprocess
import os

BASE_DIR = os.path.dirname(os.path.abspath(__file__))
FRONTEND_DIR = os.path.abspath(os.path.join(BASE_DIR, '../frontend'))
COMPILER_PATH = os.path.abspath(os.path.join(BASE_DIR, '../backend/compiler.exe'))

app = Flask(__name__, static_folder=FRONTEND_DIR, template_folder=FRONTEND_DIR)

@app.route('/')
def index():
    return render_template('index.html')

@app.route('/<path:filename>')
def serve_static(filename):
    return send_from_directory(FRONTEND_DIR, filename)

@app.route('/compile', methods=['POST'])
def compile_code():
    data = request.json
    code = data.get('code', '')
    
    if not code:
        return jsonify({'output': '', 'error': 'No code provided.'})
        
    if not os.path.exists(COMPILER_PATH):
        return jsonify({'error': 'Compiler executable not found. Please compile the C++ backend first.'})

    try:
        # Run the executable and pass code via stdin
        process = subprocess.Popen([COMPILER_PATH], stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True)
        stdout, stderr = process.communicate(input=code, timeout=5)
        
        return jsonify({
            'output': stdout,
            'error': stderr
        })
    except subprocess.TimeoutExpired:
        process.kill()
        return jsonify({'error': 'Compilation timed out.'})
    except Exception as e:
        return jsonify({'error': str(e)})

if __name__ == '__main__':
    app.run(debug=True, port=5000)
