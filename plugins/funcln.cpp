#include <cmath>
#include <limits>

extern "C" __declspec(dllexport) const char* get_function_name() {
    return "ln";
}

extern "C" __declspec(dllexport) double evaluate(double x) {
    if (x <= 0.0) {
        return std::numeric_limits<double>::quiet_NaN();
    }
    return std::log(x);
}