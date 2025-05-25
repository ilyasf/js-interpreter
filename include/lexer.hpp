#ifndef LEXER_HPP
#define LEXER_HPP

#include "token.hpp"
#include <string>

class Lexer {
public:
    explicit Lexer(const std::string& source);
    Token nextToken();
    Token peekToken();
    bool hasNext() const;

private:
    std::string source_;
    size_t position_;
    size_t line_;
    size_t column_;
    
    void skipWhitespace();
    Token readIdentifier();
    Token readNumber();
    bool isAtEnd() const;
    char advance();
    char peek() const;
    bool match(char expected);
};

#endif // LEXER_HPP 