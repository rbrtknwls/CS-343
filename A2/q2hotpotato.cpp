#include <iostream>
#include <fstream>

using namespace std;

int main( int argc, char * argv[] ) {

    istream *infile = &cin;                            // default value
    struct cmd_error {};

    intmax_t seed = getpid();

    try {
        switch (argc) {
            case 2:
                try {                                    // open input file first
                    infile = new ifstream(argv[1]);
                    break;
                } catch (uFile::Failure &) {            // open failed ?
                    cerr << "Error! Could not open input file \"" << argv[1] << "\"" << endl;
                    throw cmd_error();
                } // try
            default:                                    // wrong number of options
                throw cmd_error();
        } // switch
    } catch (...) {                                    // catch any
        cerr << "Usage: " << argv[0]
             << " [ input-file ] " << endl;
        exit(EXIT_FAILURE);                            // TERMINATE
    } // try


    cout << "hi" << endl;

}