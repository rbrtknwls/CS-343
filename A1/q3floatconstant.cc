#include <iostream>
#include <stdio.h>
#include <ctype.h>

#include "/u/r2knowles/CS-343/A1/q3floatconstant.h"

using namespace std;

int chatToInt( char c ) { return (c - '0'); }


void FloatConstant::main() {

    // Process Sign (if it exists)
    if (ch == '+') { suspend(); }
    if (ch == '-') { isPositive = false; suspend(); }

    /*
     * Until we run into a (./e/E) we can assume that we are reading in the characteristic.
    */
    while (isdigit(ch)) {
        characteristic += chatToInt(ch);
    }
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
