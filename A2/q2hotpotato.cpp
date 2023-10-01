#include <iostream>
#include <fstream>
#include <string>

#include <uPRNG.h>

using namespace std;

int main( int argc, char * argv[] ) {

    struct cmd_error {};

    intmax_t seed = getpid();
    PRNG rng(seed);

    int games = 5;
    int players = 2;

    try {
        if ( argv >= 4 ) {
            cerr << "Too many arguments!" << endl;
            throw cmd_error();
        } // if

        if ( argc > 2 ) {
            if ( argv[1] != 'd' ) { games = stoi(argv[1]); }
        } // if

        if ( argc > 3 ){
            if ( argv[2] != 'd' ) { players = stoi(argv[2]); }
        } // if

        if ( argc == 4 ) {
            if ( argv[3] != 'd' ) {
                seed = stoi(argv[3]);
            }
        } // if


    } catch (...) {
        cerr << "Usage: " << argv[0]
             << "  [ games | ’d’ [ players | ’d’ [ seed | ’d’ ] ] ] " << endl;
        exit(EXIT_FAILURE);                            // TERMINATE
    } // try


    cout << "hi" << endl;

}