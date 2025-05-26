#include "interpreter.hpp"
#include "lexer.hpp"
#include "parser.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

std::string readFile(const std::string& filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file: " + filename);
    }
    std::stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

int main(int argc, char* argv[]) {
    std::cout << "=== SIMPLE JS INTERPRETER DEVELOPED TO LEARN C++ ===" << std::endl;
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    try {
        std::string source = readFile(argv[1]);
        Lexer lexer(source);                
        Parser parser(lexer);
        auto expressions = parser.parse();
        std::cout << "=== PARSE RESULT ===" << std::endl;
        for (const auto& expr : expressions) {
            std::cout << expr->toString() << std::endl;
        }
        Interpreter interpreter;
        interpreter.interpret(expressions);
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
} 