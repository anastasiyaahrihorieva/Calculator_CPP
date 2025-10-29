#include "supports.h"

bool isNumber(const std::string& s) {
    try {
        std::stod(s);
        return true;
    } catch (...) {
        return false;
    }
}

bool isFunction(const std::string& token, const DllLoader::PluginMap& funcs) {
    return funcs.find(token) != funcs.end();
}

int priority(const std::string& op, const DllLoader::PluginMap& functions) {
    if (isFunction(op, functions)) return 3;
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    return 0; 
}