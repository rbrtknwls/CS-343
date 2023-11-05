#include <iostream>
#include <uPRNG.h>

#include "q3tallyVotes.h"
#include "q3voter.h"
#include "q3printer.h"
/*
 * Main runner for the tour group voting problem, this file will handle the input from the user and will set the
 * states for the printer, voters and tally system.
*/

using namespace std;

int main( int argc, char * argv[] ) {
    int voters = 6;
    int group = 3;
    int votes = 1;
    PRNG mainPRNG;
    int processors = 1;                                                   // default number of processors

    struct cmd_error { };

    try {

        switch (argc) {
            case 6:
                if ( *argv[5] != 'd' ) { processors = stoi(argv[5]); }
            case 5:
                if ( *argv[4] != 'd' ) {
                    int seed = stoi(argv[4]);
                  if (seed < 0) { throw cmd_error(); }
                     mainPRNG.set_seed(seed);
                }
            case 4:
                if ( *argv[3] != 'd' ) { votes = stoi(argv[3]); }
            case 3:
                if ( *argv[2] != 'd' ) { group = stoi(argv[2]); }
            case 2:
                if ( *argv[1] != 'd' ) { voters = stoi(argv[1]); }
                break;
            default:                                                      // wrong number of options
                throw cmd_error();
        } // switch

    } catch (...) {                                                       // catch any
        cerr << "Usage: " << argv[0]
             << "vote [ voters | ’d’ [ group | ’d’ [ votes | ’d’ [ seed | ’d’ [ processors | ’d’ ] ] ] ] ]"  << endl;
        exit(EXIT_FAILURE);                                               // TERMINATE
    } // try

    uProcessor p[processors - 1] __attribute__(( unused ));
}
