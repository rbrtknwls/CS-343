#include <iostream>
#include <fstream>

#include "q1binsertsort.h"

using namespace std;

template<typename T> void Binsertsort<T>::main() {
    Binsertsort<T> less;
    Binsertsort<T> more;

    std::cout << "value stored: " << value << std::endl;
    pivot = value;
    suspend();

    for ( ;; ) {

        if ( value < pivot ) {
            less.sort(value);
        } else {
            more.sort(value);
        }
        suspend();

    }

}

template<typename T> void Binsertsort<T>::sort( T value ) {                                          // value to be sorted
    Binsertsort::value = value;
    resume();
}


template<typename T> T Binsertsort<T>::retrieve() {                                                  // retrieve sorted value
    resume();
    return value;
}

int main( int argc, char * argv[] ) {

    istream *infile = &cin;                            // default value

    struct cmd_error {};

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

    _Co
    for (;;) {
        std::cout << "==== new run ====" << std::endl;
        int numberOfValuesToSort;
        if (!(*infile >> numberOfValuesToSort)) {
            break;
        }

        Binsertsort<int> tree;

        for (int i = 0; i < numberOfValuesToSort; i++) {
            int currValue;

            *infile >> currValue;
            tree.sort(currValue);
        }

    }

    if ( infile != &cin ) delete infile;
}