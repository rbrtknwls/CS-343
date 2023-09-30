#include <iostream>
#include <fstream>

#include "q1binsertsort.h"

using namespace std;

int main( int argc, char * argv[] ) {

    istream *infile = &cin;                            // default value

    struct cmd_error {};

    try {
        switch (argc) {
            case 2:
                try {                                    // open input file first
                    std::cout <<"HERE"
                    infile = new ifstream(argv[1]);
                    std::cout <<"thre"
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

    for (;;) {

        int numberOfValuesToSort;
        if (!(*infile >> numberOfValuesToSort)) {
            break;
        }

        for (int i = 0; i < numberOfValuesToSort; i++) {
            int currValue;

            *infile >> currValue;
            cout << currValue << endl;
        }

    }

    if ( infile != &cin ) delete infile;
}