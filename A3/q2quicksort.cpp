#include <iostream>
#include <fstream>
#include <math.h>
#include <uPRNG.h>

#include "q2quicksort.h"

using namespace std;

int main( int argc, char * argv[] ) {


    istream *infile = &cin;                                       // default for input stream
    ostream *outfile = &cout;                                     // default for output stream

    unsigned int depth = 0;                                       // default depth
    unsigned int size = 0;                                        // default size
    bool timeMode = false;                                        // default mode

    struct cmd_error {};

    try {

        if ( argc >= 2 && argv[1][0] == '-' ) {                   // if we see '-' assume its time mode
            timeMode = true;

            switch ( argc ) {
                case 4:
                    depth = stoi(argv[3]);                        // update depth
                case 3:
                    size = stoi(argv[2]);                         // update size
                    break;
                default:                                          // wrong number of options
                    throw cmd_error();
            } // switch

        } else {

            switch ( argc ) {
                case 4:                                            // set depth
                    depth = stoi(argv[3]);
                case 3:
                    if ( *argv[2] != 'd' ) { outfile = new ofstream(argv[2]); }
                case 2:
                  if ( *argv[1] == 'd' ) { break; }
                    try {                                          // open input file first
                        infile = new ifstream(argv[1]);
                        break;
                    } catch (uFile::Failure &) {                   // open failed
                        cerr << "Error! Could not open input file \"" << argv[1] << "\"" << endl;
                        throw cmd_error();
                    } // try
                default:                                           // wrong number of options
                    throw cmd_error();
            } // switch
        }

    } catch (...) {                                                // catch any
        cerr << "Usage: " << argv[0]
             << " ( [ unsorted-file | 'd' [ sorted-file | 'd' [ depth (>= 0) ] ] ] | "
             << "-t size (>= 0) [ depth (>= 0) ] ) " << endl;
        exit(EXIT_FAILURE);                                        // TERMINATE
    } // try



    if ( timeMode ) {

        unsigned int times = sqrt( size );                         // set time to sqrt of size
        STYPE arrayOfValues [ size ];

        // set up the array so its descending from size to 1
        for ( unsigned int counter = 0; counter < size; counter++ ) {
            arrayOfValues[counter] = size - counter;
        } // for

        // swap the indexes randomly
        for ( unsigned int counter = 0; counter < times; counter += 1 ) {
            swap( arrayOfValues[0], arrayOfValues[ prng( size ) ] );
        } // for

        uProcessor p[ (1 << depth) - 1 ] __attribute__((unused));  // 2^depth-1 kernel threads

        uTime start = uClock::currTime();                          // start the test
        quicksort( arrayOfValues, 0, size-1, depth );
        cout << "Sort time " << uClock::currTime() - start << " sec." << endl;


    } else {

        for ( ;; ) {
            int numberOfValuesToSort;
          if (!(*infile >> numberOfValuesToSort)) { break; }       // exit when we dont get new values to read

            STYPE arrayOfValues[numberOfValuesToSort];

            for (int i = 0; i < numberOfValuesToSort; i++) {
                *infile >> arrayOfValues[i];                       // save value to array
                *outfile << arrayOfValues[i];                      // output the values as we read them in

                if (i != numberOfValuesToSort - 1) { *outfile << " "; }
            }
            *outfile << endl;

            if (numberOfValuesToSort != 0) {
                quicksort(arrayOfValues, 0, numberOfValuesToSort - 1, depth);
            }

            for (int i = 0; i < numberOfValuesToSort; i++) {
                *outfile << arrayOfValues[i];                      // output the sorted values

                if (i != numberOfValuesToSort - 1) { *outfile << " "; }
            }
            *outfile << endl;
        }
    }

    if ( infile != &cin ) delete infile;                    // delete in stream pointer at end
    if ( outfile != &cout ) delete outfile;                 // delete out stream pointer at end
}