#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H

#include <stdexcept>
#include <string>

class CalculatorException : public std::runtime_error {
public:
    explicit CalculatorException(const std::string& msg);
};

class PluginException : public CalculatorException {
public:
    explicit PluginException(const std::string& msg);
};

class ParseException : public CalculatorException {
public:
    explicit ParseException(const std::string& msg);
};

class OperationException : public CalculatorException {
public:
    explicit OperationException(const std::string& msg);
};

#endif
