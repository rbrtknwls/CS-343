#include <iostream>
#include <fstream>
#include <stdio.h>
#include <ctype.h>
#include <math.h>

#include <exception>
#include <typeinfo>
#include <stdexcept>

#include "q3floatconstant.h"

using namespace std;

/* Helper Function #1 (charToInt)
 * This function lets us convert a char into an integer
 */
int charToInt( char c ) { return (c - '0'); }

/*
 * Helper Function #2 (printEmptyLine)
 * Will print the expected output for if the line is empty
 */
void printEmptyLine() {
    cout << "\"\" : Warning! Blank line." << endl;
}

/*
 * Helper Function #3 (printError)
 * Takes in the input stream and the current amount of characters read in, will then
 * print out the error output formatted to show the
 */
void printError(string *str, int i ) {
    cout << "\"" << *str << "\" : " << str.substr(0, i) << " no";                     // Print re values we have already read in
    if (i < *str->length() - 1) {
        cout << " -- extraneous characters \"" << str.substr(i, string::npos) << "\"";
    }
    std::cout <<

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
        characteristic = characteristic*10 + charToInt(ch);
        suspend();                                                               // Wait to read in the next value
    } // while

    /*
     * If we run into a '.' we can assume that the next series of digits we will be reading
     * in belong to the mantissa, therefore we will keep reading them in
     */
    if ( ch == '.' ) {
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
    if ( ch == 'e' || ch == 'E' ) {
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

    }


    if (ch == 'f' || ch == 'F' ) {
        suspend();
    } // if

    if (ch == 'l' || ch == 'L' ) {
        suspend();
    } // if

    // if we only have EOT left then we parsed successfully
    if ( ch == EOT ) {
        _Resume Match(totalFloat) _At resumer();
    } // if

    // no valid possible match left, therefore throw an error
    _Resume Error() _At resumer();
}

void FloatConstant::next(char c) {
    ch = c; // Read in the character;
    resume();
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

    for ( ;; ) { // Loop through every line in the file

        string line;
        getline(*infile, line);

        if ( infile->fail() ) { break; }

        // If line starts with new line, its empty so read it in and skip
        if ( line == "") {
            printEmptyLine();
            continue;
        } // if



        FloatConstant floatConstant;
        int i = 0;
        char ch;
        for ( ;; ) {                                     // Loop through each character on each line

            if (line[i] == '\n') { line[i] = FloatConstant::EOT; }  // Replace new line with new constant

            try {
                _Enable {
                    floatConstant.next(line[i++]);
                } // Enable

            } catch ( FloatConstant::Match & match ) {
                std::cout << "match" << std::endl;
                break;

            } catch ( FloatConstant::Error & error ) {
                std::cout << "ERROR" << std::endl;

                printError( line, i )
                break;


            }

        } // for
    } // for

    if ( infile != &cin ) delete infile;
}
