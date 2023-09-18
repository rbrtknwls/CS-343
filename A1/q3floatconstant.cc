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

    // Process sign (if it exists)
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


    totalFloat += flipInt(characteristic);                                        // characteristic done so add it
    numberOfDigits = 0;                                                           // reset number of digits

    /*
     * If we run into a '.' we can assume that the next series of digits we will be reading
     * in belong to the mantissa, therefore we will keep reading them in
     */
    if ( ch == DOT ) {
        suspend();                                                                // read in the separator

        while ( isdigit(ch) ) {
            mantissa += charToInt(ch) / pow(10, 1 + numberOfDigits++);
            suspend();
        } // while

        if ( mantissa == 0 ) { throw Error(); }                                   // Mantissa is all zeros
        totalFloat += mantissa;

    } // if

    /*
     * If we run into a (e/E) then it means all the other digits we will read in belong to the
     * exponent. Therefore, we will keep reading in values until we run out of digits.
     */
    if ( ch == EXL || ch == EXU ) {
        suspend();

        // Process exponent sign (if it exists)
        if (ch == '+') { suspend(); }
        if (ch == '-') { isExponentPositive = false; suspend(); }

        while ( isdigit(ch) ) {
            exponent += charToInt(ch) * pow(10, numberOfDigits++);
            suspend();
        } // while

        if ( exponent == 0 ) { throw Error(); }                                   // Exponent is all zeros
        exponent = flipInt(exponent);
        totalFloat *= pow(10, exponent);

    } // if

    // if we only have EOT left then we parsed successfully
    if ( ch == EOT ) {
        throw Match(totalFloat);
    } // if

    // no valid possible match left, therefore throw an error
    throw Error;

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
    floatConstant.next('1');
    floatConstant.next('\003');

    std::cout << "pls work" << std::endl;
}
