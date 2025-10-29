#include <iostream>
#include <string>

#include "calc.h"
#include "dllLoad.h"
#include "parser.h"


int main() {
    DllLoader loader("./plugins");
    auto& funcs = loader.getFunctions();

    std::string expr;
    std::cout << "Enter expression using ' ' as a delimiter: ";
    std::getline(std::cin, expr);

    try {
        double result = Calculate(expr, funcs);
        std::cout << "Result: " << result << std::endl;
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }

    return 0;
}