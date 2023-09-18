#include <iostream>
#include "/u/r2knowles/CS-343/A1/q3floatconstant.h"
using namespace std;

void FloatConstant::main() {

    // Process Sign (if it exists)
    if (ch == '+') { suspend(); }
    if (ch == '-') { isPositive = false; suspend(); }
    
    cout << "Silly Billy" << endl;

}

void FloatConstant::next(char c) {
    cout <<  c << "hi" << endl;
    resume();
}

int main() {
    FloatConstant floatConstant;
    floatConstant.next('e');
    std::cout << "pls work" << std::endl;
}
