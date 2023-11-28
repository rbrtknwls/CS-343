#include <iostream>
#include <vector>
#include <uPRNG.h>

using namespace std;

PRNG mainPRNG;

int main( int argc, char * argv[] ) {

    char * configFile;
    int processors = 0;

    struct cmd_error { };

    try {
        switch ( argc ) {
            case 4:
                if ( *argv[3] != 'd' ) { processors = stoi(argv[3]); }
            case 3:
                if ( *argv[2] != 'd' ) {
                    int seed = stoi(argv[2]);
                  if (seed <= 0) { throw cmd_error(); }
                    mainPRNG.set_seed(seed);
                }
            case 2:
                if ( *argv[1] != 'd' ) { configFile = stoi(argv[1]); }
            default:
                if ( processors <= 0 ) { throw cmd_error(); }
                break;
        }

    } catch (...) {
        cerr << "Usage: " << argv[0]
             << " [ config-file | ’d’ [ seed (> 0) | ’d’ [ processors (> 0) | ’d’ ] ] ]"  << endl;
        exit(EXIT_FAILURE);
    }

    uProcessor p[processors - 1] __attribute__(( unused ));


}
