#include <iostream>
#include <fstream>

#include "q1binsertsort.h"

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

    for (;;) {
        int numberOfValuesToSort;
        *infile >> numberOfValuesToSort;

        for (int i = 0; i < numberOfValuesToSort; i++) {
            int currValue;

            *infile >> currValue
        }
    }
}

