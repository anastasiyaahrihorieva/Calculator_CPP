#ifndef EXPRESSIONPARSER_H
#define EXPRESSIONPARSER_H

#include <string>
#include <vector>
#include <memory>
#include <unordered_map>
#include "IOperation.h"

class ExpressionParser {
public:
    explicit ExpressionParser(const std::vector<std::shared_ptr<IOperation>>& operations);
    virtual ~ExpressionParser() = default;
    double evaluate(const std::string& expression, const std::vector<std::shared_ptr<IOperation>>& operations);

protected:
    virtual void preProcess(std::string& expr);
    virtual std::vector<std::string> tokenize(const std::string& expr);
    virtual double applyOperator(const std::string& op, const std::vector<double>& args, const std::vector<std::shared_ptr<IOperation>>& operations);
    int precedence(const std::string& op) const;
    bool isNumber(const std::string& tok) const;
    bool isFunctionName(const std::string& tok, const std::vector<std::shared_ptr<IOperation>>& ops) const;
};

#endif
