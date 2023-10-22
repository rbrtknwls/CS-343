#include <iostream>
#include <string>
#include "q2quicksort.h"

using namespace std;

int main( int argc, char * argv[] ) {

    istream *infile = &cin;
    ostream *outfile = &cout;

    struct cmd_error {};

    try {

        if ( argc < 2 ) { throw cmd_error }

        if ( argv[1][0] == '-' ) {

        } else {
            switch (argc) {
                case 3:
                    if ( argv[2] != 'd' ) { outfile = new ofstream(argv[2]); }

                case 2:
                    if ( argv[1] == 'd' ) { break; }
                    try {                                      // open input file first
                        infile = new ifstream(argv[1]);
                        break;
                    } catch (uFile::Failure &) {               // open failed
                        cerr << "Error! Could not open input file \"" << argv[1] << "\"" << endl;
                        throw cmd_error();
                    } // try

                default:                                       // wrong number of options
                    throw cmd_error();
            } // switch
        }
    } catch (...) {                                        // catch any
        cerr << "Usage: " << argv[0]
             << " unsorted-file [ sorted-file ] " << endl;
        exit(EXIT_FAILURE);                                // TERMINATE
    } // try
}