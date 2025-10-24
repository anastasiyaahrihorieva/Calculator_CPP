#include "Calculator.h"
#include "BaseOperation.h"       // для AddOperation, MulOperation и т.д.
#include "ExpressionParser.h"    // для парсера выражений
#include "PluginManager.h"       // для загрузки плагинов
#include "Exceptions.h"          // для обработки исключений
#include "IOperation.h"          // базовый интерфейс операций
#include <iostream>              // для ввода/вывода
#include <sstream>               // для работы со строками
#include <cmath>                 // для std::floor, std::isfinite

Calculator& Calculator::instance() {
    static Calculator C;
    return C;
}

Calculator::Calculator()
{
    pluginManager_ = std::make_unique<PluginManager>();
    registerBuiltinOperations();
    parser_ = std::make_unique<ExpressionParser>(builtinOperations_);
}

Calculator::~Calculator() = default;

void Calculator::registerBuiltinOperations()
{
    builtinOperations_.push_back(std::make_shared<AddOperation>());
    builtinOperations_.push_back(std::make_shared<MinusOperation>());
    builtinOperations_.push_back(std::make_shared<MulOperation>());
    builtinOperations_.push_back(std::make_shared<DivOperation>());
}

void Calculator::loadPlugins(const std::string& path)
{
    pluginManager_->loadPlugins(path);
    auto funcs = pluginManager_->getOperations();
    for (auto& f : funcs)
        builtinOperations_.push_back(f);
    parser_ = std::make_unique<ExpressionParser>(builtinOperations_);
}

double Calculator::evaluate(const std::string& expr)
{
   return parser_->evaluate(expr, builtinOperations_);
}

std::vector<std::shared_ptr<IOperation>> Calculator::availableOperations() const
{
    return builtinOperations_;
}

void Calculator::run()
{
    try {
        loadPlugins("./plugins");
    } catch (const std::exception& e) {
        std::cerr << "Plugin load error: " << e.what() << std::endl;
    }

    std::cout << "Calculator ready. Type 'exit' to quit.\n";
    std::string expr;

    while (true) {
        std::cout << "> ";
        if (!std::getline(std::cin, expr)) break;
        if (expr == "exit") break;
        if (expr.empty()) continue;

        try {
            double result = evaluate(expr);
            if (std::isfinite(result)) {
                if (std::floor(result) == result)
                    std::cout << static_cast<long long>(result) << std::endl;
                else
                    std::cout << result << std::endl;
            } else {
                std::cout << "Result not finite" << std::endl;
            }
        } catch (const std::exception& e) {
            std::cout << "Error: " << e.what() << std::endl;
        } catch (...) {
            std::cout << "Unknown error" << std::endl;
        }
    }
}
