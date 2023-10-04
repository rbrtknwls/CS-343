#include <iostream>
#include <fstream>

#include "q1binsertsort.h"

using namespace std;

template<typename T> void Binsertsort<T>::main() {
    _Coroutine Binsertsort<T> less;
    _Coroutine Binsertsort<T> more;

    pivot = value;

    try{
        _Enable {
                // At this point a node does not have any children, so it should
                //    trigger an exception to its parent and return the value
        }
    } catch (Sentinel & sentinel) {
        _Resume Sentinel() _At resumer();
        suspend();
    }

    suspend();

    // Keep adding values to tree until we reach an exception
    for ( ;; ) {
        try {
            _Enable {

                if ( value < pivot ) {
                    less.sort(value);
                } else {
                    more.sort(value);
                }

                suspend();

            }
        } catch ( Sentinel & sentinel ){
            _Resume Sentinel() _At less;
            break;
        }

    }

    // Loop through left children
    for ( ;; ) {
        value = less.retrieve();
        try {
            _Enable{
                suspend();
            }
        } catch ( Sentinel & sentinel ){
            break;
        }
    }
    value = pivot;

    suspend();
    _Resume Sentinel() _At more;

    for ( ;; ) {
        value = more.retrieve();
        try {
            _Enable{

                suspend();

            }
        } catch ( Sentinel & sentinel ){
            break;
        }
    }

    // Raise an exception at anything that trys to reacd this node
    _Resume Sentinel() _At resumer();



}

template<typename T> Binsertsort<T>::Binsertsort() {}

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
    ostream *outfile = &cout;                          // default value

    struct cmd_error {};

    try {
        switch (argc) {
            case 3:
                outfile = new ofstream(argv[2]);
            case 2:
                try {                                    // open input file first
                    infile = new ifstream(argv[1]);
                    break;
                } catch (uFile::Failure &) {            // open failed
                    cerr << "Error! Could not open input file \"" << argv[1] << "\"" << endl;
                    throw cmd_error();
                } // try
            default:                                    // wrong number of options
                throw cmd_error();
        } // switch
    } catch (...) {                                    // catch any
        cerr << "Usage: " << argv[0]
             << " unsorted-file [ sorted-file ] " << endl;
        exit(EXIT_FAILURE);                            // TERMINATE
    } // try


    for ( ;; ) {

        int numberOfValuesToSort;
        if (!(*infile >> numberOfValuesToSort)) {
            break;
        }

            Binsertsort<TYPE> tree;

            for (int i = 0; i < numberOfValuesToSort; i++) {
                TYPE currValue;

                *infile >> currValue;
                *outfile << currValue;
                if (i != numberOfValuesToSort - 1) { *outfile << " "; }
                tree.sort(currValue);
            }
            *outfile << endl;

            _Resume Binsertsort<TYPE>::Sentinel() _At tree;


            try {
                _Enable {
                    *outfile << tree.retrieve();
                    for ( ;; ) {
                        TYPE valRetrieved = tree.retrieve();
                        *outfile << " " << valRetrieved;
                    }
                }

            } catch (Binsertsort<TYPE>::Sentinel &sentinel) {
                *outfile << endl;
            }

            *outfile << endl;
    }

    if ( infile != &cin ) delete infile;
}