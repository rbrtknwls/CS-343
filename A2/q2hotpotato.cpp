#include <iostream>
#include <fstream>
#include <string>

#include <uPRNG.h>
#include "q2hotpotato.h"

using namespace std;

int main( int argc, char * argv[] ) {

    struct cmd_error {};

    intmax_t seed = getpid();
    PRNG mainPRNG(seed);

    int games = 5;
    int players = mainPRNG(2, 10);

    try {
        if ( argc > 4 ) {
            cerr << "Too many arguments!" << endl;
            throw cmd_error();
        } // if

        if ( argc >= 2 ) {
            if ( *argv[1] != 'd' ) { games = stoi( argv[1] ); }
        } // if

        if ( argc >= 3 ){
            if ( *argv[2] != 'd' ) { players = stoi( argv[2] ); }
        } // if

        if ( argc == 4 ) {
            if ( *argv[3] != 'd' ) {
                seed = stoi( argv[3] );
                mainPRNG.set_seed( seed );

                if ( *argv[2] == 'd' ) { players = mainPRNG( 2, 10 ); }
            } // if
        } // if


    } catch (...) {
        cerr << "Usage: " << argv[0]
             << "  [ games | ’d’ [ players | ’d’ [ seed | ’d’ ] ] ] " << endl;
        exit(EXIT_FAILURE);                            // TERMINATE
    } // try


    // Initial set up
    PRNG playerPRNG( seed );
    PRNG potatoPRNG( seed );
    Potato potato( potatoPRNG );

    cout << players << " players in the game" << endl;
    int swappedPlayer = mainPRNG(1,players-1);

    cout << games << endl;
    cout << "hi" << endl;

}