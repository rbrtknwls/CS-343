#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#include "/u/r2knowles/CS-343/A1/q3floatconstant.h"

using namespace std;

int charToInt( char c ) { return (c - '0'); }


void FloatConstant::main() {

    // Process Sign (if it exists)
    if (ch == '+') { suspend(); }
    if (ch == '-') { isFloatPositive = false; suspend(); }

    /*
     * Until we run into a (./e/E) we can assume that we are reading in the characteristic.
     * Note that these are in the wrong order, so after we are done reading in values we will
     * need to flip them.
    */
    while (isdigit(ch)) {
        characteristic += charToInt(ch) * pow(10, numberOfDigits++);
        suspend();                                                               // Wait to read in the next value
    }

    if (ch == 'E' || ch == 'e' || ch == '.')
    cout << characteristic << endl;

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
