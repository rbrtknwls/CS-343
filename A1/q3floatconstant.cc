#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#include "q3floatconstant.h"

using namespace std;

/* Helper Function #1 (charToInt)
 * This function lets us convert a char into an integer
 */
int charToInt( char c ) { return (c - '0'); }

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
        characteristic = characteristic*10 + charToInt(ch);
        suspend();                                                               // Wait to read in the next value
    } // while

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
            exponent += exponent*10 + charToInt(ch);
            suspend();
        } // while

        if ( exponent == 0 ) { throw Error(); }                                   // Exponent is all zeros
        totalFloat *= pow(10, exponent);

    } // if


    if (ch == FSL || ch == FSU ) {
        suspend();
    } // if

    if (ch == LSL || ch == FSU ) {
        suspend();
    } // if

    // if we only have EOT left then we parsed successfully
    if ( ch == EOT ) {
        _Throw Match(totalFloat);
    } // if

    // no valid possible match left, therefore throw an error
    _Throw Error();
}

void FloatConstant::next(char c) {
    ch = c; // Read in the character;
    try {
        resume();
    } _CatchResume ( Match &mc ) {
        cout << "MATCH" << endl;
    } _CatchResume ( Error &er ) {
        cout << "ERROR" << endl;
    }
}

int main( int argc, char * argv[] ) {

    istream * infile = &cin;							// default value

    struct cmd_error {};

    try {
        switch ( argc ) {
            case 2:
                try {								    // open input file first as output creates file
                    infile = new ifstream( argv[1] );
                } catch( uFile::Failure & ) {		    // open failed ?
                    cerr << "Error! Could not open input file \"" << argv[3] << "\"" << endl;
                    throw cmd_error();
                } // try
                // FALL THROUGH
            case 1:										// defaults
                break;
            default:								    // wrong number of options
                throw cmd_error();
        } // switch
    } catch( ... ) {									// catch any
        cerr << "Usage: " << argv[0]
             << " [ input-file ] " << endl;
        exit( EXIT_FAILURE );							// TERMINATE
    } // try

    char ch;
    for ( ;; ) { // Loop through every line in the file
        if ( infile->fail() ) { break; }

        //FloatConstant floatConstant;

        bool isOnlyChar = true;                          // Check if line is only '\n'
        std::string numberSoFar = "";
        for ( ;; ) {                                     // Loop through each character on each line

            infile->get(ch);

            if ( infile->fail() ) { break; }

            if (ch == '\n') {                            // End of Line

                if (isOnlyChar) {
                    cout << "\"" << numberSoFar << "\"" << ": Warning! Blank line." << endl;
                    break;
                } else {
                    std::cout << " OVER\n";
                }
                break;
            } // if

            isOnlyChar = false;
            std::cout << ch;
            numberSoFar += ch;

        } // for
    } // for

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

    if ( infile != &cin ) delete infile;
}
