#include "BaseOperation.h"
#include <stdexcept>


BaseOperation::BaseOperation(std::string name, int argc) 
    : name_(std::move(name)), argc_(argc) {}

int BaseOperation::arity() const {
    return argc_;
}

std::string BaseOperation::name() const {
    return name_;
}

AddOperation::AddOperation() : BaseOperation("+", 2) {}

double AddOperation::execute(const std::vector<double>& args) {
    return args[0] + args[1];
}
  
MulOperation::MulOperation() : BaseOperation("*", 2) {}

double MulOperation::execute(const std::vector<double>& args) {
    return args[0] * args[1];
}

MinusOperation::MinusOperation() : BaseOperation("-", 2) {}

double MinusOperation::execute(const std::vector<double>& args) {
    return args[0] - args[1];
}

DivOperation::DivOperation() : BaseOperation("/", 2) {}

double DivOperation::execute(const std::vector<double>& args) {
    if (args[1] == 0) {
        throw std::runtime_error("Division by zero");
    }
    return args[0] / args[1];
}