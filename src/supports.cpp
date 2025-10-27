#include "main.h"

bool isNumber(const std::string &s)
{
    return !s.empty() && (std::isdigit(s[0]) ||
                          ((s[0] == '-' || s[0] == '+') && s.size() > 1 && std::isdigit(s[1])));
}

int priority(const std::string &op)
{
    if (op == "+" || op == "-")
    {
        return 1;
    }

    else if (op == "*" || op == "/")
    {
        return 2;
    }

    return 0;
}