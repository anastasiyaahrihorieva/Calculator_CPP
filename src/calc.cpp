#include "main.h"
#include "parser.cpp"

std::vector<std::string> RPN_Parser(std::string &consoleExpr);

double Calculate(std::string &consoleExpr) {
    std::vector<std::string> parsed_expr = RPN_Parser(consoleExpr);
    std::stack<double> st;
    
    for (auto &token : parsed_expr) {
        if (isNumber(token)) {
            st.push(std::stod(token));
        } else {
            double b = st.top(); st.pop();
            double a = st.top(); st.pop();
            
            switch(token[0]) {
                case '+': st.push(a + b); break;
                case '-': st.push(a - b); break;
                case '*': st.push(a * b); break;
                case '/': st.push(a / b); break;
            }
        }
    }
    return st.top();
}