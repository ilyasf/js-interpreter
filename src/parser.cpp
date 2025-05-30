#include "parser.hpp"
#include "lexer.hpp"
#include "token.hpp"
#include <sstream>
#include <stdexcept>
#include <memory>
#include <vector>
#include <iostream>

// First, add this new class to your Expression hierarchy
class VariableDeclaration : public Expression {
public:
    VariableDeclaration(const std::string& name, std::shared_ptr<Expression> initializer)
        : name_(name), initializer_(initializer) {}
    
    std::string toString() const override {
        return "const " + name_ + " = " + initializer_->toString();
    }

private:
    std::string name_;
    std::shared_ptr<Expression> initializer_;
};

std::string NumberLiteral::toString() const {
    return std::to_string(value_);
}

std::string Identifier::toString() const {
    return name_;
}

std::string CallExpression::toString() const {
    std::stringstream ss;
    ss << callee_ << "(";
    for (size_t i = 0; i < arguments_.size(); ++i) {
        if (i > 0) ss << ", ";
        ss << arguments_[i]->toString();
    }
    ss << ")";
    return ss.str();
}

Parser::Parser(Lexer& lexer) : lexer_(lexer) {
    advance();
}

std::vector<std::shared_ptr<Expression>> Parser::parse() {
    std::vector<std::shared_ptr<Expression>> expressions;
    printToken(current_);
    
    while (!check(TokenType::EOF_TOKEN)) {
        if (check(TokenType::SEMICOLON)) {
            advance(); // skip semicolon
            continue;
        }
        
        expressions.push_back(parseExpression());
        // consume(TokenType::SEMICOLON, "Expected ';' after expression");
    }
    
    return expressions;
}

std::shared_ptr<Expression> Parser::parseExpression() {
    if (match(TokenType::CONST)) {
        Token name = consume(TokenType::IDENTIFIER, "Expected variable name after 'const'.");
        consume(TokenType::EQUALS, "Expected '=' after variable name.");
        return std::make_shared<VariableDeclaration>(std::get<std::string>(name.value), parsePrimary());
    }
    
    return parsePrimary();
}

std::shared_ptr<Expression> Parser::parsePrimary() {
    if (match(TokenType::NUMBER)) {
        return std::make_shared<NumberLiteral>(std::get<double>(previous_.value));
    }
    
    if (match(TokenType::IDENTIFIER) || match(TokenType::LOG)) {
        std::string name = std::get<std::string>(previous_.value);
        
        if (match(TokenType::DOT)) {
            if (match(TokenType::LOG)) {
                previous_.value = std::string("console.log");
                return parseCall();
            }
            throw std::runtime_error("Unsupported method call: " + name + "." + std::get<std::string>(previous_.value));
        }
        
        return std::make_shared<Identifier>(name);
    }
    
    if (match(TokenType::INPUT)) {
        return std::make_shared<CallExpression>("input", std::vector<std::shared_ptr<Expression>>());
    }
    printToken(previous_);
    throw std::runtime_error("Unexpected token in expression");
}

std::shared_ptr<Expression> Parser::parseCall() {
    std::string callee = std::get<std::string>(previous_.value);
    std::vector<std::shared_ptr<Expression>> arguments;
    
    consume(TokenType::LPAREN, "Expected '(' after function name.");
    
    if (!check(TokenType::RPAREN)) {
        do {
            arguments.push_back(parsePrimary());
        } while (match(TokenType::COMMA));
    }
    
    consume(TokenType::RPAREN, "Expected ')' after arguments.");
    
    return std::make_shared<CallExpression>(callee, arguments);
}

void Parser::advance() {
    previous_ = current_;
    current_ = lexer_.nextToken();
}

bool Parser::check(TokenType type) const {
    return current_.type == type;
}

bool Parser::match(TokenType type) {
    if (check(type)) {
        advance();
        return true;
    }
    return false;
}

Token Parser::consume(TokenType type, const std::string& message) {
    if (check(type)) {
        Token token = current_;
        advance();
        return token;
    }
    throw std::runtime_error(message);
}

void Parser::printToken(const Token& token) const {
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