#include "lexer.hpp"
#include <cctype>
#include <stdexcept>

Lexer::Lexer(const std::string& source)
    : source_(source), position_(0), line_(1), column_(1) {}

Token Lexer::nextToken() {
    skipWhitespace();

    if (isAtEnd()) {
        return Token{TokenType::EOF_TOKEN, "", line_, column_};
    }

    char c = peek();

    if (std::isalpha(c)) {
        return readIdentifier();
    }

    if (std::isdigit(c)) {
        return readNumber();
    }

    switch (c) {
        case '=':
            advance();
            return Token{TokenType::EQUALS, "=", line_, column_ - 1};
        case ';':
            advance();
            return Token{TokenType::SEMICOLON, ";", line_, column_ - 1};
        case '.':
            advance();
            return Token{TokenType::DOT, ".", line_, column_ - 1};
        case '(':
            advance();
            return Token{TokenType::LPAREN, "(", line_, column_ - 1};
        case ')':
            advance();
            return Token{TokenType::RPAREN, ")", line_, column_ - 1};
        case ',':
            advance();
            return Token{TokenType::COMMA, ",", line_, column_ - 1};
        default:
            throw std::runtime_error("Unexpected character: " + std::string(1, c));
    }
}

Token Lexer::peekToken() {
    size_t currentPos = position_;
    size_t currentLine = line_;
    size_t currentColumn = column_;
    
    Token token = nextToken();
    
    position_ = currentPos;
    line_ = currentLine;
    column_ = currentColumn;
    
    return token;
}

bool Lexer::hasNext() const {
    return !isAtEnd();
}

void Lexer::skipWhitespace() {
    while (!isAtEnd() && std::isspace(peek())) {
        if (peek() == '\n') {
            line_++;
            column_ = 1;
        } else {
            column_++;
        }
        advance();
    }
}

Token Lexer::readIdentifier() {
    size_t start = position_;
    size_t startColumn = column_;

    while (!isAtEnd() && (std::isalnum(peek()) || peek() == '_')) {
        advance();
    }

    std::string text = source_.substr(start, position_ - start);
    TokenType type;

    if (text == "const") {
        type = TokenType::CONST;
    } else if (text == "console") {
        type = TokenType::IDENTIFIER;
    } else if (text == "log") {
        type = TokenType::LOG;
    } else if (text == "input") {
        type = TokenType::INPUT;
    } else {
        type = TokenType::IDENTIFIER;
    }

    return Token{type, text, line_, startColumn};
}

Token Lexer::readNumber() {
    size_t start = position_;
    size_t startColumn = column_;

    while (!isAtEnd() && std::isdigit(peek())) {
        advance();
    }

    std::string numberStr = source_.substr(start, position_ - start);
    double number = std::stod(numberStr);
    return Token{TokenType::NUMBER, number, line_, startColumn};
}

bool Lexer::isAtEnd() const {
    return position_ >= source_.length();
}

char Lexer::advance() {
    char current = peek();
    position_++;
    column_++;
    return current;
}

char Lexer::peek() const {
    if (isAtEnd()) return '\0';
    return source_[position_];
}

bool Lexer::match(char expected) {
    if (isAtEnd() || peek() != expected) return false;
    advance();
    return true;
} 