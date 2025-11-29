#include "wrapper.h"
#include <iostream>

void Subject::f3(int arg1, int arg2) {
    std::cout << "f3 called with arg1=" << arg1 << ", arg2=" << arg2 << std::endl;
}

void Subject::f4(int arg1, int arg2, int arg3) {
    std::cout << "f4 called with arg1=" << arg1 << ", arg2=" << arg2 << ", arg3=" << arg3 << std::endl;
}

void Subject::f5(int a, int b, int c, int d) {
    std::cout << "f5 called with a=" << a << ", b=" << b << ", c=" << c << ", d=" << d << std::endl;
}