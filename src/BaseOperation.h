#ifndef BASEOPERATION_H
#define BASEOPERATION_H

#include "IOperation.h"
#include <stdexcept>
#include <string>

class BaseOperation : public IOperation {
public:
    explicit BaseOperation(std::string name, int argc);
    int arity() const override;
    std::string name() const override;

protected:
    std::string name_;
    int argc_;
};

class AddOperation : public BaseOperation {
public:
    AddOperation();
    double execute(const std::vector<double>& args) override;
};

class MulOperation : public BaseOperation {
public:
    MulOperation();
    double execute(const std::vector<double>& args) override;
};

class MinusOperation : public BaseOperation {
public:
    MinusOperation();
    double execute(const std::vector<double>& args) override;
};

class DivOperation : public BaseOperation {
public:
    DivOperation();
    double execute(const std::vector<double>& args) override;
};

#endif
