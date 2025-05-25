#ifndef PARSER_HPP
#define PARSER_HPP

#include "lexer.hpp"
#include <memory>
#include <string>
#include <vector>

// Abstract base class for all expressions
class Expression {
public:
    virtual ~Expression() = default;
    virtual std::string toString() const = 0;
};

// Expression for numeric literals
class NumberLiteral : public Expression {
public:
    explicit NumberLiteral(double value) : value_(value) {}
    std::string toString() const override;
    friend class Interpreter;

private:
    double value_;
};

// Expression for identifiers
class Identifier : public Expression {
public:
    explicit Identifier(const std::string& name) : name_(name) {}
    std::string toString() const override;
    friend class Interpreter;

private:
    std::string name_;
};

// Expression for function calls
class CallExpression : public Expression {
public:
    CallExpression(const std::string& callee, std::vector<std::shared_ptr<Expression>> args)
        : callee_(callee), arguments_(std::move(args)) {}
    std::string toString() const override;
    friend class Interpreter;

private:
    std::string callee_;
    std::vector<std::shared_ptr<Expression>> arguments_;
};

// Parser class
class Parser {
public:
    explicit Parser(Lexer& lexer);
    std::vector<std::shared_ptr<Expression>> parse();

private:
    Lexer& lexer_;
    Token current_;
    Token previous_;

    std::shared_ptr<Expression> parseExpression();
    std::shared_ptr<Expression> parsePrimary();
    std::shared_ptr<Expression> parseCall();
    void advance();
    bool check(TokenType type) const;
    bool match(TokenType type);
    Token consume(TokenType type, const std::string& message);
};

#endif // PARSER_HPP 