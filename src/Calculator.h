#ifndef CALCULATOR_H
#define CALCULATOR_H

#include <memory>
#include <string>
#include <vector>
#include "ExpressionParser.h"
#include "PluginManager.h"
#include "IOperation.h"

class Calculator {
public:
    static Calculator& instance();

    void run();
    double evaluate(const std::string& expr);
    void loadPlugins(const std::string& path);
    std::vector<std::shared_ptr<IOperation>> availableOperations() const;

    Calculator(const Calculator&) = delete;
    Calculator& operator=(const Calculator&) = delete;

private:
    Calculator();
    ~Calculator();

    std::unique_ptr<ExpressionParser> parser_;
    std::unique_ptr<PluginManager> pluginManager_;
    std::vector<std::shared_ptr<IOperation>> builtinOperations_;
    void registerBuiltinOperations();
};

#endif
