#ifndef IOPERATION_H
#define IOPERATION_H

#include <string>
#include <vector>
#include <memory>

class IOperation {
public:
    virtual ~IOperation() = default;
    virtual double execute(const std::vector<double>& args) = 0;
    virtual int arity() const = 0;
    virtual std::string name() const = 0;
};

using OperationPtr = std::shared_ptr<IOperation>;

#endif
