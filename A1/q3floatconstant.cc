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
 * Takes in the current line and the position of the last index, will then
 * print out the error output formatted.
 */
void printError( string *str, unsigned int i ) {
    cout << "\"" << *str << "\" : \"" << str->substr(0, i) << "\" no";          // Print values we have read in
    if ( i + 1 < str->length() ) {                                              // if left over values print them
        cout << " -- extraneous characters \"" << str->substr(i, string::npos) << "\"";
    }
    cout << endl;                                                               // create a new line
}

/*
 * Helper Function #4 (printMatch)
 * Takes in the current line and the double we get from the match printing out the
 * output to be formatted correctly.
 */
void printMatch( string *line, double match ) {
    cout << "\"" << *line << "\" : \"" << *line << "\" yes, value ";            // Should be the same for a match
    cout << match << endl;                                                      // print the matching value
}

void FloatConstant::main() {
    // Initialize our values during our next()
    isFloatPositive = true; isExponentPositive = true; numberOfDigits = 0;
    mantissa = 0; characteristic = 0; exponent = 0; totalFloat = 0;             // Set the required state values



    // Process sign (if it exists)
    if (ch == '+') { isFloatPositive = true; suspend(); }
    if (ch == '-') { isFloatPositive = false; suspend(); }

    /*
     * Until we run into a (./e/E) we can assume that we are reading in the characteristic.
     * Note that these are in the wrong order, so after we are done reading in values we will
     * need to flip them.
    */
    while ( isdigit(ch) ) {
        characteristic = characteristic*10 + charToInt(ch);
        suspend();                                                                // wait to read in the next value
    } // while

    // If we have only digits that's not a valid float, so if we get EOT now is an error
    if ( ch == EOT ) { _Resume Error() _At resumer(); suspend(); }

    totalFloat += characteristic;                                                 // once done reading, move to result
    if ( !isFloatPositive ) { totalFloat *= -1; }                                 // make the value negative

    /*
     * If we run into a '.' we can assume that the next series of digits we will be reading
     * in belong to the mantissa, therefore we will keep reading them in
     */
    if ( ch == '.' ) {
        suspend();                                                                // read in the separator

        while ( isdigit(ch) ) {
            mantissa += charToInt(ch) / pow(10, ++numberOfDigits);
            suspend();
        } // while

        //if ( mantissa == 0 ) { throw Error(); }                                   // Mantissa is all zeros
        totalFloat += mantissa;

    } // if

    /*
     * If we run into a (e/E) then it means all the other digits we will read in belong to the
     * exponent. Therefore, we will keep reading in values until we run out of digits.
     */
    if ( ch == 'e' || ch == 'E' ) {
        suspend();

        // Process exponent sign (if it exists)
        if (ch == '+') { isExponentPositive = true; suspend(); }
        if (ch == '-') { isExponentPositive = false; suspend(); }

        while ( isdigit(ch) ) {
            exponent += exponent*10 + charToInt(ch);
            suspend();
        } // while

        //if ( exponent == 0 ) { throw Error(); }                                   // Exponent is all zeros
        totalFloat *= pow(10, exponent);

    }

    if (ch == 'f' || ch == 'F' || ch == 'l' || ch == 'L') {
        suspend();
    } // if

    // if we only have EOT left then we parsed successfully
    if ( ch == EOT ) {
        _Resume Match(totalFloat) _At resumer();
        suspend();
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
        if ( line == "" ) {
            printEmptyLine();
            continue;
        } // if


        line += FloatConstant::EOT;                                                   // Add end of text character

        FloatConstant floatConstant;
        for ( unsigned int i = 0 ; i < line.length() ; ) {                                     // Loop through each character on each line

            try {
                _Enable {
                    floatConstant.next(line[i++]);
                } // Enable

            } catch ( FloatConstant::Match & match ) {
                printMatch( &line, match.value );
                break;

            } catch ( FloatConstant::Error & error ) {
                printError( &line, i );
                break;
            }

        } // for
    } // for

    if ( infile != &cin ) delete infile;
}
