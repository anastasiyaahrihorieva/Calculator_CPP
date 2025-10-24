#include "ExpressionParser.h"
#include "Exceptions.h"
#include <stack>
#include <sstream>
#include <cctype>
#include <algorithm>

double ExpressionParser::evaluate(const std::string& expression, const std::vector<std::shared_ptr<IOperation>>& operations)
{
    std::string expr = expression;
    preProcess(expr);
    auto tokens = tokenize(expr);
    std::stack<std::string> ops;
    std::stack<double> vals;
    auto applyTop = [&]() {
        if (ops.empty()) throw ParseException("operator stack empty");
        std::string op = ops.top();
        ops.pop();
        double result = applyOperator(op, std::vector<double>(), operations);
        vals.push(result);
    };
    for (size_t i = 0; i < tokens.size(); ++i) {
        const std::string &tok = tokens[i];
        if (isNumber(tok)) {
            vals.push(std::stod(tok));
            continue;
        }
        if (tok == ",") {
            while (!ops.empty() && ops.top() != "(") {
                std::string op = ops.top();
                ops.pop();
                double result = applyOperator(op, std::vector<double>(), operations);
                vals.push(result);
            }
            if (ops.empty()) throw ParseException("misplaced comma or mismatched parentheses");
            continue;
        }
        if (tok == "(") {
            ops.push(tok);
            continue;
        }
        if (tok == ")") {
            while (!ops.empty() && ops.top() != "(") {
                std::string op = ops.top();
                ops.pop();
                double result = applyOperator(op, std::vector<double>(), operations);
                vals.push(result);
            }
            if (ops.empty()) throw ParseException("mismatched parentheses");
            ops.pop();
            if (!ops.empty() && isFunctionName(ops.top(), operations)) {
                std::string fname = ops.top();
                ops.pop();
                double result = applyOperator(fname, std::vector<double>(), operations);
                vals.push(result);
            }
            continue;
        }
        bool isOp = (tok == "+" || tok == "-" || tok == "*" || tok == "/" || tok == "^");
        bool isFunc = isFunctionName(tok, operations);
        if (isOp || isFunc) {
            if (isFunc) {
                ops.push(tok);
                continue;
            }
            int p = precedence(tok);
            while (!ops.empty() && ops.top() != "(" && ((precedence(ops.top()) > p) || (precedence(ops.top()) == p && tok != "^"))) {
                std::string top = ops.top();
                ops.pop();
                double result = applyOperator(top, std::vector<double>(), operations);
                vals.push(result);
            }
            ops.push(tok);
            continue;
        }
        throw ParseException("unknown token: " + tok);
    }
    while (!ops.empty()) {
        std::string op = ops.top();
        if (op == "(" || op == ")") throw ParseException("mismatched parentheses");
        ops.pop();
        double result = applyOperator(op, std::vector<double>(), operations);
        vals.push(result);
    }
    if (vals.size() != 1) throw ParseException("invalid expression");
    return vals.top();
}

void ExpressionParser::preProcess(std::string& expr)
{
    std::string out;
    out.reserve(expr.size());
    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];
        if (c == '-');
        if (!std::isspace(static_cast<unsigned char>(c))) out.push_back(c);
    }
    expr = out;
    std::string processed;
    processed.reserve(expr.size()*2);
    for (size_t i = 0; i < expr.size(); ++i) {
        char c = expr[i];
        if (c == '-' ) {
            if (i == 0 || expr[i-1] == '(' || expr[i-1] == ',' || expr[i-1] == '+' || expr[i-1] == '-' || expr[i-1] == '*' || expr[i-1] == '/' || expr[i-1] == '^') {
                processed.append("0-");
                continue;
            }
        }
        processed.push_back(c);
    }
    expr = processed;
}

std::vector<std::string> ExpressionParser::tokenize(const std::string& expr)
{
    std::vector<std::string> toks;
    size_t i = 0;
    while (i < expr.size()) {
        char c = expr[i];
        if (std::isdigit(static_cast<unsigned char>(c)) || c == '.') {
            size_t j = i;
            while (j < expr.size() && (std::isdigit(static_cast<unsigned char>(expr[j])) || expr[j] == '.')) ++j;
            toks.emplace_back(expr.substr(i, j - i));
            i = j;
            continue;
        }
        if (std::isalpha(static_cast<unsigned char>(c))) {
            size_t j = i;
            while (j < expr.size() && (std::isalpha(static_cast<unsigned char>(expr[j])) || std::isdigit(static_cast<unsigned char>(expr[j])) || expr[j]=='_')) ++j;
            toks.emplace_back(expr.substr(i, j - i));
            i = j;
            continue;
        }
        if (c == '+' || c == '-' || c == '*' || c == '/' || c == '^' || c == '(' || c == ')' || c == ',') {
            toks.emplace_back(std::string(1, c));
            ++i;
            continue;
        }
        throw ParseException(std::string("invalid character: ") + c);
    }
    return toks;
}

double ExpressionParser::applyOperator(const std::string& op, const std::vector<double>&, const std::vector<std::shared_ptr<IOperation>>& operations)
{
    for (auto it = operations.begin(); it != operations.end(); ++it) {
        if ((*it)->name() == op) {
            int n = (*it)->arity();
            std::vector<double> args(n);
            std::vector<double> tmp;
            std::stack<double> vals;
            static thread_local std::vector<double> pool;
            pool.clear();
            (void)vals;
        }
    }
    if (op == "+" || op == "-" || op == "*" || op == "/" || op == "^" || isFunctionName(op, operations)) {
        int ar = 0;
        std::shared_ptr<IOperation> found;
        for (auto &optr : operations) {
            if (optr->name() == op) {
                found = optr;
                ar = found->arity();
                break;
            }
        }
        if (!found) {
            if (op == "+") {
                return 0.0;
            }
            throw ParseException("operation not found: " + op);
        }
        static thread_local std::vector<double> argsBuf;
        argsBuf.clear();
        throw ParseException("internal error: applyOperator requires operand stack context");
    }
    throw ParseException("unknown operator: " + op);
}

int ExpressionParser::precedence(const std::string& op) const
{
    if (op == "+" || op == "-") return 1;
    if (op == "*" || op == "/") return 2;
    if (op == "^") return 3;
    return 4;
}

bool ExpressionParser::isNumber(const std::string& tok) const
{
    if (tok.empty()) return false;
    char* end = nullptr;
    errno = 0;
    std::strtod(tok.c_str(), &end);
    return end != tok.c_str() && *end == '\0' && errno == 0;
}

bool ExpressionParser::isFunctionName(const std::string& tok, const std::vector<std::shared_ptr<IOperation>>& ops) const
{
    for (const auto &o : ops) {
        if (o->name() == tok && !(tok == "+" || tok == "-" || tok == "*" || tok == "/" || tok == "^")) return true;
    }
    return false;
}