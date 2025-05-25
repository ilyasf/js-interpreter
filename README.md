# Simple JavaScript Interpreter

A simple JavaScript interpreter created for educational purposes. The project implements a basic parser and interpreter for a subset of JavaScript.

## Features

- Lexical Analyzer (Lexer)
- Parser
- Interpreter
- Support for basic JavaScript constructs:
  - Constant declarations
  - Value assignments
  - Function calls
  - Number and string operations
  - Input/output operations

## Requirements

- C++17
- Clang++ compiler
- Make

## Building

```bash
make clean  # Clean previous build
make        # Build the project
```

## Usage

```bash
./build/program input.js
```

## Project Structure

```
.
├── include/           # Header files
│   ├── lexer.hpp
│   ├── parser.hpp
│   ├── interpreter.hpp
│   └── token.hpp
├── src/              # Source code
│   ├── main.cpp
│   ├── lexer.cpp
│   ├── parser.cpp
│   └── interpreter.cpp
├── build/            # Build directory
├── Makefile         # Build file
└── README.md        # Documentation
```

## Code Example

```javascript
const x = 42;
const message = "Hello, World!";
log(message);
const input = input();
log(input);
```

## Contributing

Contributions are welcome! Please follow these guidelines:

- All code comments and documentation **must be written in English**.
- Follow the existing code style and structure.
- Make sure your code builds and passes all tests before submitting a pull request.
- Describe your changes clearly in the pull request.

## License

MIT License

Copyright (c) 2024

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE. 