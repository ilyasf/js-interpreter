#ifndef INTERPRETER_HPP
#define INTERPRETER_HPP

#include "parser.hpp"
#include <string>
#include <unordered_map>

class Interpreter {
public:
    Interpreter() = default;
    void interpret(const std::vector<std::shared_ptr<Expression>>& expressions);

private:
    std::unordered_map<std::string, double> variables_;
    
    double evaluate(const std::shared_ptr<Expression>& expr);
    double evaluateNumber(const std::shared_ptr<NumberLiteral>& expr);
    double evaluateIdentifier(const std::shared_ptr<Identifier>& expr);
    double evaluateCall(const std::shared_ptr<CallExpression>& expr);
};

#endif // INTERPRETER_HPP 