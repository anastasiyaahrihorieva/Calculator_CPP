#include "main.h"
#include "supports.cpp"
std::vector<std::string> RPN_Parser(std::string &consoleExpr)
{
    std::vector<std::string> result;
    std::stack<std::string> opStack;
    std::istringstream iss(consoleExpr);
    std::string token;

    while (iss >> token)
    {
        if (isNumber(token))
        {
            result.push_back(token);

        } else if (token == "(")
        {
            opStack.push(token);

        } else if (token == ")")
        {
            while (!opStack.empty() && opStack.top() != "(") {
                result.push_back(opStack.top());
                opStack.pop();
            }

            if (!opStack.empty())
                opStack.pop();
        }
        else
        {
            while (!opStack.empty() && priority(opStack.top()) >= priority(token))
            {
                result.push_back(opStack.top());
                opStack.pop();
            }
            opStack.push(token);
        }
    }

    while (!opStack.empty())
    {
        result.push_back(opStack.top());
        opStack.pop();
    }

    return result;
}