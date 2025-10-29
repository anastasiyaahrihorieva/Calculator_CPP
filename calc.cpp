#include "calc.h"

double Calculate(std::string& consoleExpr, const DllLoader::PluginMap& functions) {
    std::vector<std::string> parsed_expr = RPN_Parser(consoleExpr, functions);
    std::stack<double> st;

    for (auto& token : parsed_expr) {
        if (isNumber(token)) {
            st.push(std::stod(token));
        } else if (isFunction(token, functions)) {
            
            if (st.size() < 1) throw std::runtime_error("Not enough operands for function " + token);
            double x = st.top(); st.pop();
            st.push(functions.at(token)(x));
        } else {
            
            if (st.size() < 2) throw std::runtime_error("Not enough operands for operator " + token);
            double b = st.top(); st.pop();
            double a = st.top(); st.pop();

            switch(token[0]) {
                case '+': st.push(a + b); break;
                case '-': st.push(a - b); break;
                case '*': st.push(a * b); break;
                case '/': 
                    if (b == 0) throw std::runtime_error("Division by zero");
                    st.push(a / b); break;
                default:
                    throw std::runtime_error("Unknown operator: " + token);
            }
        }
    }

    if (st.size() != 1) throw std::runtime_error("Invalid expression");
    return st.top();
}

