#include <iostream>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#include "/u/r2knowles/CS-343/A1/q3floatconstant.h"

using namespace std;

/* Helper Function #1 (charToInt)
 * This function lets us convert a char into an integer
 */
int charToInt( char c ) { return (c - '0'); }

/* Helper Function #2 (flipInt)
 * This function lets us flip an integer in a pretty quick way,
 * this lets us read in values and place them into one of the categories
 * very quickly O(n)!
 */
int flipInt( int valToFlip ) {
    int val = 0;

    while ( valToFlip > 0 ) {
        val        = 10*val + valToFlip%10;
        valToFlip /= 10;
    }

    return val;
}

void FloatConstant::main() {

    // Process Sign (if it exists)
    if (ch == '+') { suspend(); }
    if (ch == '-') { isFloatPositive = false; suspend(); }

    /*
     * Until we run into a (./e/E) we can assume that we are reading in the characteristic.
     * Note that these are in the wrong order, so after we are done reading in values we will
     * need to flip them.
    */
    while ( isdigit(ch) ) {
        characteristic += charToInt(ch) * pow(10, numberOfDigits++);
        suspend();                                                               // Wait to read in the next value
    } // while


    // At this point we want to check if the non digit we have is valid
    if ( ch != EOT && ch != EXL && ch != EXU && ch != DOT &&
         ch != FSL && ch != FSU && ch != LSL && ch != LSU ) {
        throw Error();
    } // if
    totalFloat += flipInt(characteristic);                                           // characteristic done so add it
    numberOfDigits = 0;                                                           // reset number of digits

    if ( ch == DOT ) {
        suspend();                                                                // read in the separator

        while ( isdigit(ch) ) {
            mantissa += charToInt(ch) / pow(10, 1 + numberOfDigits++);
            suspend();
        }

    } // if

    cout << totalFloat << endl;

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
    floatConstant.next('e');
    std::cout << "pls work" << std::endl;
}
