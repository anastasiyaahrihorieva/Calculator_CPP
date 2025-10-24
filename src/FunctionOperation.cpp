#include "FunctionOperation.h"

FunctionOperation::FunctionOperation(std::string name, PluginFunc fn, int argc)
    : name_(name), fn_(fn), argc_(argc) {}

double FunctionOperation::execute(const std::vector<double>& args) {
    return fn_(args.data(), argc_);
}

int FunctionOperation::arity() const {
    return argc_;
}

std::string FunctionOperation::name() const {
    return name_;
}