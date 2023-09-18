#include <iostream>
#include <stdio.h>
#include <ctype.h>

#include "/u/r2knowles/CS-343/A1/q3floatconstant.h"

using namespace std;

int chatToInt( char c ) { return (c - '0'); }


void FloatConstant::main() {

    // Process Sign (if it exists)
    if (ch == '+') { suspend(); }
    if (ch == '-') { isFloatPositive = false; suspend(); }

    /*
     * Until we run into a (./e/E) we can assume that we are reading in the characteristic.
    */
    while (isdigit(ch)) {
        characteristic += chatToInt(ch);
        suspend();
    }
    cout << "Silly Billy" << endl;

}

void FloatConstant::next(char c) {
    ch = c; // Read in the character;
    resume();
}

int main() {
    FloatConstant floatConstant;
    floatConstant.next('+');
    floatConstant.next('1');
    floatConstant.next('2');
    floatConstant.next('.');
    floatConstant.next('5');
    floatConstant.next('6');
    std::cout << "pls work" << std::endl;
}
