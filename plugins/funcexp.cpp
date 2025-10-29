#include <cmath>

extern "C" __declspec(dllexport) const char* get_function_name() {
    return "exp";
}

extern "C" __declspec(dllexport) double evaluate(double x) {
    return std::exp(x);
}