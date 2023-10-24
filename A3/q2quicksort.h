#ifndef CS_343_Q2SORTINGIMPL_H
#define CS_343_Q2SORTINGIMPL_H

#include <iostream>
#include <uCobegin.h>
#include <uActor.h>

using namespace std;


// ======================= "Helper Methods" =======================
/*
 * Custom type used to return from a function, while I could use a tuple, I like the style of defining my own array
 *  as I think it makes it clearer what values exactly are contained. This will be used to return the left and
 *  right bounds from our partition method
 */
typedef unsigned int PartResults[2];

/*
 * We can reuse the same partition method for each of the implementations. Having one method can help reduce the
 *   amount of repeated code
 */
template<typename T> void partition ( T values[], unsigned int low, unsigned int high, PartResults *returnVals ) {
    unsigned int pivotIdx = low + (high - low) / 2;                     // choose a pivot index

    unsigned int i = low;                                               // set new height to be low
    unsigned int j = high;                                              // set new floor to be high

    for ( ;; ) {
        // while each value from low is less then pivot, keep going
        while (values[i] < values[pivotIdx]) i++;
        // while each value from low is greater then pivot, keep going
        while (values[j] > values[pivotIdx]) j--;

      if ( i > j ) { break; }                                           // once height is bigger then floor break

        swap(values[i], values[j]);                                     // swap i and j
        i++;
        if (j != 0) { j--; }
    } // for

    (*returnVals)[0] = i;                                               // save i to return values
    (*returnVals)[1] = j;                                               // save j to return values

}

/*
 * Once the depth is 0 we need to use sequential quicksort; since this applys for all 3 implementations,
 *   it makes sense to implement it once
 */
template<typename T> void sequentialQuicksort( T values[], unsigned int low, unsigned int high ) {
  if ( low >= high ) { return; }                                        // exit once high and low are equal or lower

    PartResults results;                                                // set up results
    partition(values, low, high, &results);

    unsigned int i = results[0];
    unsigned int j = results[1];


    sequentialQuicksort( values, low, j );                         // do quick sorts on left side
    sequentialQuicksort( values, i, high );                         // do quick sort on right side

}

// ======================= Method Implementation =======================

#if defined( TASK )
// Task implimentation of a quicksort
template<typename T> _Task SortWithTask {
    T *values;
    unsigned int low;
    unsigned int high;
    unsigned int depth;

    void main() {

      if ( low >= high ) { return; }                                      // exit condition

        if ( depth == 0 ) {
            sequentialQuicksort(values, low, high);                       // at depth zero start doing sequential sort
        } else {
            PartResults results;                                          // set up an results
            partition(values, low, high, &results);
            unsigned int i = results[0];
            unsigned int j = results[1];


            SortWithTask left(values, low, j, depth-1);                   // make a new task for the left
            sequentialQuicksort(values, i, high);                         // continue on the right
        } // if
    } // main()

  public:
    // generic constructors
    SortWithTask( T *values, unsigned int low, unsigned int high, unsigned int depth ) : values(values), low(low), high(high), depth(depth) {}
};

#elif defined( ACTOR )
// Actor message for the quick sort
struct SortMsg : public uActor::Message {
    STYPE *values;
    unsigned int low;
    unsigned int high;
    unsigned int depth;

    SortMsg( STYPE *values, unsigned int low, unsigned int high, unsigned int depth ) :
        Message(uActor::Delete), values(values), low(low), high(high), depth(depth) {}
};

// Actor for quick sort
_Actor SortWithActor {
    Allocation receive( uActor::Message & msg ) {
        Case( SortMsg, msg ) {
            // extract the message values
            STYPE *values = msg_d->values;
            unsigned int low = msg_d->low;
            unsigned int high = msg_d->high;
            unsigned int depth = msg_d->depth;

            if ( depth == 0 || low >= high ) { sequentialQuicksort( values, low, high ); } else {

                // if depth is not zero do quick sort on either side
                PartResults results;
                partition(values, low, high, &results);
                unsigned int i = results[0];
                unsigned int j = results[1];
                *new SortWithActor() | *new SortMsg( values, low, j, depth-1 ) | uActor::stopMsg;
                *new SortWithActor() | *new SortMsg( values, i, high, depth-1 ) | uActor::stopMsg;

            } // if
        } else Case( StopMsg, msg ) return Delete;
        return uActor::Nodelete;
    } // allocation


};

#endif

/*
 * We use only a single quicksort function, depending on the compiler variables we will change the implementation
 */
template<typename T> void quicksort( T values[], unsigned int low, unsigned int high, unsigned int depth ) {
  if ( low >= high ) { return; }

    if ( depth == 0 ) {                                                    // if depth is zero, run sequential sort
        sequentialQuicksort( values, low, high );
        return;
    } // if

#if defined( CBEGIN )
    uThisTask().verify();

    PartResults results;
    partition(values, low, high, &results);
    unsigned int i = results[0];
    unsigned int j = results[1];

    // use coroutines and run quicksort on the left and right
    COBEGIN
        BEGIN quicksort( values, low, j, depth-1 ); END
        BEGIN quicksort( values, i, high, depth-1 ); END
    COEND

#elif defined( TASK )
    SortWithTask sort( values, low, high, depth );

#elif defined( ACTOR )
    uActor::start();
    *new SortWithActor() | *new SortMsg( values, low, high, depth ) | uActor::stopMsg;
    uActor::stop();
#endif
}


#endif //CS_343_Q2SORTINGIMPL_H