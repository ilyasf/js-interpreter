#include "interpreter.hpp"
#include <iostream>
#include <stdexcept>

void Interpreter::interpret(const std::vector<std::shared_ptr<Expression>>& expressions) {
    for (const auto& expr : expressions) {
        evaluate(expr);
    }
}

double Interpreter::evaluate(const std::shared_ptr<Expression>& expr) {
    if (auto number = std::dynamic_pointer_cast<NumberLiteral>(expr)) {
        return evaluateNumber(number);
    }
    if (auto identifier = std::dynamic_pointer_cast<Identifier>(expr)) {
        return evaluateIdentifier(identifier);
    }
    if (auto call = std::dynamic_pointer_cast<CallExpression>(expr)) {
        return evaluateCall(call);
    }
    throw std::runtime_error("Unknown expression type");
}

double Interpreter::evaluateNumber(const std::shared_ptr<NumberLiteral>& expr) {
    return expr->value_;
}

double Interpreter::evaluateIdentifier(const std::shared_ptr<Identifier>& expr) {
    const std::string& name = expr->name_;
    auto it = variables_.find(name);
    if (it == variables_.end()) {
        throw std::runtime_error("Undefined variable: " + name);
    }
    return it->second;
}

double Interpreter::evaluateCall(const std::shared_ptr<CallExpression>& expr) {
    const std::string& callee = expr->callee_;
    
    if (callee == "console.log") {
        if (expr->arguments_.empty()) {
            throw std::runtime_error("console.log() requires at least one argument");
        }
        double value = evaluate(expr->arguments_[0]);
        std::cout << value << std::endl;
        return value;
    }
    
    if (callee == "input") {
        if (!expr->arguments_.empty()) {
            throw std::runtime_error("input() takes no arguments");
        }
        double value;
        std::cin >> value;
        return value;
    }
    
    throw std::runtime_error("Unknown function: " + callee);
} 