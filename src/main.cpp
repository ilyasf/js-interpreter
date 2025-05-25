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

void printToken(const Token& token) {
    std::cout << "Token: ";
    switch (token.type) {
        case TokenType::CONST: std::cout << "CONST"; break;
        case TokenType::IDENTIFIER: std::cout << "IDENTIFIER"; break;
        case TokenType::EQUALS: std::cout << "EQUALS"; break;
        case TokenType::NUMBER: std::cout << "NUMBER"; break;
        case TokenType::SEMICOLON: std::cout << "SEMICOLON"; break;
        case TokenType::DOT: std::cout << "DOT"; break;
        case TokenType::LOG: std::cout << "LOG"; break;
        case TokenType::INPUT: std::cout << "INPUT"; break;
        case TokenType::LPAREN: std::cout << "LPAREN"; break;
        case TokenType::RPAREN: std::cout << "RPAREN"; break;
        case TokenType::COMMA: std::cout << "COMMA"; break;
        case TokenType::EOF_TOKEN: std::cout << "EOF"; break;
    }
    std::cout << ", value: ";
    if (std::holds_alternative<std::string>(token.value)) {
        std::cout << std::get<std::string>(token.value);
    } else if (std::holds_alternative<double>(token.value)) {
        std::cout << std::get<double>(token.value);
    }
    std::cout << ", line: " << token.line << ", col: " << token.column << std::endl;
}

int main(int argc, char* argv[]) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <filename>" << std::endl;
        return 1;
    }

    try {
        std::string source = readFile(argv[1]);
        Lexer lexer(source);
        std::cout << "=== TOKENS ===" << std::endl;
        Token t;
        do {
            t = lexer.nextToken();
            printToken(t);
        } while (t.type != TokenType::EOF_TOKEN);
        std::cout << "=== PARSING ===" << std::endl;
        Lexer lexer2(source); // New lexer instance for parser
        Parser parser(lexer2);
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