document.addEventListener('DOMContentLoaded', () => {
    const compileBtn = document.getElementById('compile-btn');
    const clearBtn = document.getElementById('clear-btn');
    const codeEditor = document.getElementById('code-editor');
    const outputDisplay = document.getElementById('output-display');
    const themeToggle = document.getElementById('theme-toggle');

    // Theme toggle
    themeToggle.addEventListener('click', () => {
        document.body.classList.toggle('dark-theme');
        if (document.body.classList.contains('dark-theme')) {
            themeToggle.textContent = '☀️ Light Mode';
        } else {
            themeToggle.textContent = '🌙 Dark Mode';
        }
    });

    // Syntax highlighting setup
    const highlightingContent = document.getElementById('highlighting-content');
    const highlighting = document.getElementById('highlighting');

    function updateHighlighting(text) {
        let result = text.replace(new RegExp("&", "g"), "&amp;").replace(new RegExp("<", "g"), "&lt;");
        highlightingContent.innerHTML = result;
        Prism.highlightElement(highlightingContent);
    }

    codeEditor.addEventListener('input', () => {
        updateHighlighting(codeEditor.value);
    });

    codeEditor.addEventListener('scroll', () => {
        highlighting.scrollTop = codeEditor.scrollTop;
        highlighting.scrollLeft = codeEditor.scrollLeft;
    });

    // Initial highlight call if there's predefined text
    updateHighlighting(codeEditor.value);

    // Clear output
    clearBtn.addEventListener('click', () => {
        outputDisplay.innerHTML = '';
    });

    // Dynamic output color injection
    function colorizeOutput(text) {
        let lines = text.split('\n');
        let result = [];
        for (let line of lines) {
            if (line.includes('Output:')) {
                result.push(`\n<span class="colored-header">${line}</span>`);
            } else if (line.includes('Innovation Twist:')) {
                result.push(`\n<span class="colored-header">${line}</span>`);
            } else if (line.includes('=')) {
                // TAC operations coloring
                result.push(`<span class="colored-tac">${line}</span>`);
            } else if (line.startsWith('[')) {
                // Assembly execution order coloring
                result.push(`<span class="colored-exec">${line}</span>`);
            } else if (line.includes('Error')) {
                result.push(`<span class="error-text">${line}</span>`);
            } else {
                result.push(line);
            }
        }
        return result.join('\n');
    }

    compileBtn.addEventListener('click', async () => {
        const sourceCode = codeEditor.value.trim();
        
        if (!sourceCode) {
            outputDisplay.innerHTML = '<span class="error-text">Please enter some code to compile! ✨</span>';
            return;
        }

        compileBtn.classList.add('loading');
        compileBtn.disabled = true;
        outputDisplay.textContent = 'Compiling...';

        try {
            const response = await fetch('/compile', {
                method: 'POST',
                headers: { 'Content-Type': 'application/json' },
                body: JSON.stringify({ code: sourceCode })
            });

            if (!response.ok) throw new Error(`HTTP Error: ${response.status}`);

            const data = await response.json();
            
            if (data.error && !data.output) {
                outputDisplay.innerHTML = `<span class="error-text">Server Error:\n${data.error}</span>`;
            } else {
                let formattedOut = colorizeOutput(data.output || "");
                if (data.error) {
                    formattedOut += `\n<span class="error-text">${data.error}</span>`;
                }
                outputDisplay.innerHTML = formattedOut;
            }

        } catch (err) {
            outputDisplay.innerHTML = `<span class="error-text">Connection Failed:\n${err.message}</span>`;
        } finally {
            compileBtn.classList.remove('loading');
            compileBtn.disabled = false;
        }
    });

    // Handle indentation
    codeEditor.addEventListener('keydown', function(e) {
        if (e.key == 'Tab') {
            e.preventDefault();
            let start = this.selectionStart;
            let end = this.selectionEnd;
            this.value = this.value.substring(0, start) + "    " + this.value.substring(end);
            this.selectionStart = this.selectionEnd = start + 4;
        }
    });
});
