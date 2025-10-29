#include <cmath>

extern "C" __declspec(dllexport) const char* get_function_name() {
    return "sqrt"; 
}

extern "C" __declspec(dllexport) double evaluate(double x) {
    return pow(x, 2); 
}