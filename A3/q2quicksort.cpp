#include <iostream>
#include <fstream>
#include <string>
#include "q2quicksort.h"

using namespace std;

int main( int argc, char * argv[] ) {

    istream *infile = &cin;
    ostream *outfile = &cout;
    int depth = 0;
    int size = 0;
    bool timeMode = false;

    struct cmd_error {};

    try {

        if ( argc >= 2 && argv[1][0] == '-' ) {
            timeMode = true;

            switch ( argc ) {
                case 4:
                    depth = stoi(argv[3]);
                  if ( depth < 0 ) { cmd_error(); }
                case 3:
                    size = stoi(argv[2]);
                  if ( size >= 0 ) { break; }
                default:                                       // wrong number of options
                    throw cmd_error();
            }

        } else {

            switch ( argc ) {
                case 4:
                    depth = stoi(argv[3]);
                  if ( depth < 0 ) { throw cmd_error(); }
                case 3:
                    if ( *argv[2] != 'd' ) { outfile = new ofstream(argv[2]); }

                case 2:
                  if ( *argv[1] == 'd' ) { break; }
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
             << " ( [ unsorted-file | 'd' [ sorted-file | 'd' [ depth (>= 0) ] ] ] | "
             << "-t size (>= 0) [ depth (>= 0) ] ) " << endl;
        exit(EXIT_FAILURE);                                // TERMINATE
    } // try



    if ( timeMode ) {

    } else {


        for ( ;; ) {

            int numberOfValuesToSort;
            if (!(*infile >> numberOfValuesToSort)) { break; }

            TYPE arrayOfValues [numberOfValuesToSort];
            for (int i = 0; i < numberOfValuesToSort; i++) {
                *infile >> arrayOfValues[i]
                *outfile << *infile;
                if (i != numberOfValuesToSort - 1) { *outfile << " "; }
            }


        }
    }
}