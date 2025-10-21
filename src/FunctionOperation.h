#ifndef FUNCTIONOPERATION_H
#define FUNCTIONOPERATION_H

#include "IOperation.h"
#include <functional>
#include <string>
#include <vector>
#include <stdexcept>

using PluginFunc = double(*)(const double* args, int argc);

class FunctionOperation : public IOperation {
public:
    FunctionOperation(std::string name, PluginFunc fn, int argc);
    ~FunctionOperation() override = default;
    double execute(const std::vector<double>& args) override;
    int arity() const override;
    std::string name() const override;

private:
    std::string name_;
    PluginFunc fn_;
    int argc_;
};

#endif
