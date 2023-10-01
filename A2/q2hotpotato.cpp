#include <iostream>
#include <fstream>
#include <uPRNG.h>


using namespace std;

int main( int argc, char * argv[] ) {

    istream *infile = &cin;                            // default value
    struct cmd_error {};

    intmax_t seed = getpid();
    PRNG rng(seed);

    int games = 5;
    int players = 2;

    try {
        if (argc >= 4) {
            cerr << "Too many arguments!" << endl;
            throw cmd_error();
        } // if

        if (argc > 2) {
            if ( argv[1] != 'd' ) { games = argv[1] }
        } // if

        if (argc > 3){
            if ( argv[2] != 'd' ) { players = argv[2] }
        } // if

        if (argc > 4) {
            if ( argv[3] != 'd' ) {
                seed = argv[3]
            }
        } // if


    } catch (...) {
        cerr << "Usage: " << argv[0]
             << "  [ games | ’d’ [ players | ’d’ [ seed | ’d’ ] ] ] " << endl;
        exit(EXIT_FAILURE);                            // TERMINATE
    } // try


    cout << "hi" << endl;

}