#include <iostream>
#include <fstream>
#include <math.h>
#include <uPRNG.h>

#include "q2quicksort.h"

using namespace std;

int main( int argc, char * argv[] ) {

    istream *infile = &cin;
    ostream *outfile = &cout;

    unsigned int depth = 0;
    unsigned int size = 0;
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

        unsigned int times = sqrt( size );
        STYPE *arrayOfValues  = new STYPE[ size ];

        for ( unsigned int counter = 0; counter < times; counter += 1 ) {
            swap( arrayOfValues[0], arrayOfValues[prng( size ) ] );
        } // for

        uProcessor p[ (1 << depth) - 1 ]; // 2^depth-1 kernel threads

        uTime start = uClock::currTime();
        quicksort( arrayOfValues, 0, size-1, depth );
        cout << "Sort time " << uClock::currTime() - start << " sec." << endl;

        delete[] arrayOfValues;

    } else {

        for ( ;; ) {
            int numberOfValuesToSort;
          if (!(*infile >> numberOfValuesToSort)) { break; }

            STYPE *arrayOfValues  = new STYPE[numberOfValuesToSort];
            for (int i = 0; i < numberOfValuesToSort; i++) {
                *infile >> arrayOfValues[i];
                *outfile << arrayOfValues[i];

                if (i != numberOfValuesToSort - 1) { *outfile << " "; }
            }
            *outfile << endl;

            if (numberOfValuesToSort != 0) {
                //quicksort(arrayOfValues, 0, numberOfValuesToSort - 1, depth);
            }

            for (int i = 0; i < numberOfValuesToSort; i++) {
                *outfile << arrayOfValues[i];

                if (i != numberOfValuesToSort - 1) { *outfile << " "; }
            }
            *outfile << endl;

            delete[] arrayOfValues;
        }
    }

    if ( infile != &cin ) delete infile;                    // delete in stream pointer at end
    if ( outfile != &cout ) delete outfile;                 // delete out stream pointer at end
}