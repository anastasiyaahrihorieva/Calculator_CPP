#include<string>
#include<iostream>
#include"calc.cpp"

int main(){
    std::string expr;
    std::cout << "Enter yout expression: ";
    std::getline(std::cin, expr); 
    double res = Calculate(expr);
    std::cout << "Result: " << res << std::endl;
    return 0;
}