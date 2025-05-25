#ifndef TOKEN_HPP
#define TOKEN_HPP

#include <string>
#include <variant>

enum class TokenType {
    CONST,
    IDENTIFIER,
    EQUALS,
    NUMBER,
    SEMICOLON,
    DOT,
    LOG,
    INPUT,
    LPAREN,
    RPAREN,
    COMMA,
    EOF_TOKEN
};

struct Token {
    TokenType type;
    std::variant<std::string, double> value;
    size_t line;
    size_t column;
};

#endif // TOKEN_HPP 