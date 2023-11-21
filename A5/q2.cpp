#include <iostream>
#include <vector>
#include <uPRNG.h>

#include "q2tallyVotes.h"
#include "q2voter.h"
#include "q2printer.h"

/*
 * Main runner for the tour group voting problem, this file will handle the input from the user and will set the
 * states for the printer, voters and tally system.
*/

using namespace std;

PRNG mainPRNG;                                                            // PRNG to be used by all classes

int main( int argc, char * argv[] ) {
    int voters = 6;                                                       // default number of voters
    int group = 3;                                                        // default group size
    int votes = 1;                                                        // default number of votes
    int processors = 1;                                                   // default number of processors

    struct cmd_error { };

    try {
        switch ( argc ) {
            case 6:
                if ( *argv[5] != 'd' ) { processors = stoi(argv[5]); }    // update if not 'd'
            case 5:
                if ( *argv[4] != 'd' ) {
                    int seed = stoi(argv[4]);                             // update seed if not 'd'
                  if (seed <= 0) { throw cmd_error(); }                   // catch bad input
                     mainPRNG.set_seed(seed);
                }
            case 4:
                if ( *argv[3] != 'd' ) { votes = stoi(argv[3]); }         // update votes if not 'd'
            case 3:
                if ( *argv[2] != 'd' ) { group = stoi(argv[2]); }         // update group if not 'd'
            case 2:
                if ( *argv[1] != 'd' ) { voters = stoi(argv[1]); }        // update voters if not 'd'
            default:                                                      // wrong number of options

              // Below we check if any of the values are below the accepted, if so throw an error
              if ( voters <= 0 || group <= 0 || votes <= 0 || processors <= 0 ) { throw cmd_error(); }
                break;
        } // switch

    } catch (...) {                                                       // catch any
        cerr << "Usage: " << argv[0]
             << " [ voters | ’d’ [ group | ’d’ [ votes | ’d’ [ seed | ’d’ [ processors | ’d’ ] ] ] ] ]"  << endl;
        exit(EXIT_FAILURE);                                               // TERMINATE
    } // try
    uProcessor p[processors - 1] __attribute__(( unused ));               // Set the number of processors

    Printer printer = Printer( voters );                                  // Set up our printer
    /*
    TallyVotes voteTallier = TallyVotes( voters, group, printer );        // Set up the vote tallier
    vector< Voter* > listOfVoters;                                        // Set up a list of voters

    for ( int id = 0; id < voters; id++ ) {
        listOfVoters.push_back(new Voter( id, votes, voteTallier, printer ));
    }

    for ( int id = 0; id < voters; id++ ) {
        delete listOfVoters[listOfVoters.size()-1];                       // Delete voter once done
        listOfVoters.pop_back();
    }

    listOfVoters.clear();                                                 // Clear the list
     */
}
