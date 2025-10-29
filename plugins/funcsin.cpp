#include <cmath>

extern "C" __declspec(dllexport) const char* get_function_name() {
    return "sin";
}

extern "C" __declspec(dllexport) double evaluate(double x) {
    return std::sin(x);
}