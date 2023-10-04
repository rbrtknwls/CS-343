#include <iostream>
#include <fstream>

#include "q1binsertsort.h"

using namespace std;

/*
 * This is the main co-route we will run, because we are only dealing with a single object I defined it all
 *  within main. However for Q2 I made sure to split them up. Now each node has a couple different states:
 *      1) Its parent was created but it was not. In which case if it gets sentinel just return
 *      2) It has a value and therefore should check all its children when it gets sentinel
 */
template<typename T> void Binsertsort<T>::main() {
    _Coroutine Binsertsort<T> less;                 // Coroutine for value smaller
    _Coroutine Binsertsort<T> more;                 // Coroutine for value greater

    try {
        _Enable{

            pivot = value;                          // Value we pivot on
        } // enable
    } catch (Sentinel & sentinel) { // If we get an exception here we want to return nothing and propagate error
        _Resume Sentinel() _At resumer();
        suspend();
    } // try

    suspend();

    /*
     * This is our main loop, if a coroutine makes it into this loop then it has a value assigned to it.
     *  This comes with the obligation of checking each of its children before it returns and exception.
     */
    try {
        _Enable{
            for ( ;; ) {
                if ( value < pivot ) {
                    less.sort(value);                  // Pass value to less than
                } else {
                    more.sort(value);                  // Pass value to greater than
                }

                suspend();
            } // for
        } // enable
    } catch ( Sentinel & sentinel ){
        _Resume Sentinel() _At less;                   // Start with left tree
        break;
    } // try



    /* Loop through left tree until all the children are done, note the try is done within the for loop as
     *  when we exit we want value to be populated
     */
    for ( ;; ) {
        value = less.retrieve();                       // Store left tree's value
        try {
            _Enable{
                suspend();
            } // enable
        } catch ( Sentinel & sentinel ){
            break;
        } // try
    } // for

    value = pivot;                                     // Return own value
    suspend();
    _Resume Sentinel() _At more;

    /* Loop through right tree until all the children are done, note the try is done within the for loop as
     *  when we exit we want value to be populated.
     */
    for ( ;; ) {
        value = more.retrieve();
        try {
            _Enable{
                suspend();
            } // enable
        } catch ( Sentinel & sentinel ){
            break;
        } // try
    } // for

    _Resume Sentinel() _At resumer();                   // Return to caller

}

template<typename T> Binsertsort<T>::Binsertsort() {}

// Method for saving a value
template<typename T> void Binsertsort<T>::sort( T value ) {
    Binsertsort::value = value;
    resume();
}

// Method for retrieving a value
template<typename T> T Binsertsort<T>::retrieve() {
    resume();
    return value;
}

int main( int argc, char * argv[] ) {

    istream *infile = &cin;                                // default value
    ostream *outfile = &cout;                              // default value

    struct cmd_error {};

    try {
        switch (argc) {
            case 3:
                outfile = new ofstream(argv[2]);
            case 2:
                try {                                      // open input file first
                    infile = new ifstream(argv[1]);
                    break;
                } catch (uFile::Failure &) {               // open failed
                    cerr << "Error! Could not open input file \"" << argv[1] << "\"" << endl;
                    throw cmd_error();
                } // try
            default:                                       // wrong number of options
                throw cmd_error();
        } // switch
    } catch (...) {                                        // catch any
        cerr << "Usage: " << argv[0]
             << " unsorted-file [ sorted-file ] " << endl;
        exit(EXIT_FAILURE);                                // TERMINATE
    } // try


    for ( ;; ) {

        int numberOfValuesToSort;                          // number of values to sort
      if (!(*infile >> numberOfValuesToSort)) { break; }   // if we reach end of file we should stop

        Binsertsort<TYPE> tree;                            // setup the tree

        for (int i = 0; i < numberOfValuesToSort; i++) {
            TYPE currValue;

            *infile >> currValue;                          // read value from stream
            *outfile << currValue;                         // send value to stream
            if (i != numberOfValuesToSort - 1) { *outfile << " "; }
            tree.sort(currValue);                          // sort the value
        } // for

        *outfile << endl;
        _Resume Binsertsort<TYPE>::Sentinel() _At tree;    // start getting values back


        try {
            _Enable {
                *outfile << tree.retrieve();               // print first value in tree
                for ( ;; ) {
                    // We get the value before we print it, in the case an exception will occur (no empty space)!
                    TYPE valRetrieved = tree.retrieve();
                    *outfile << " " << valRetrieved;
                } // for
            } // enable

        } catch (Binsertsort<TYPE>::Sentinel &sentinel) {
            *outfile << endl;
        } // try

        *outfile << endl;
    }

    if ( infile != &cin ) delete infile;                    // delete in stream pointer at end
    if ( outfile != &cout ) delete outfile;                 // delete out stream pointer at end
}