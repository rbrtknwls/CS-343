#ifndef CS_343_Q2SORTINGIMPL_H
#define CS_343_Q2SORTINGIMPL_H

#include <iostream>
#include <uCobegin.h>
#include <uActor.h>

using namespace std;

typedef unsigned int PartResults[2];

template<typename T> void partition ( T values[], unsigned int low, unsigned int high, PartResults *returnVals ) {
    unsigned int pivotIdx = low + (high - low) / 2;

    unsigned int i = low;
    unsigned int j = high;

    for ( ;; ) {
        while (values[i] < values[pivotIdx]) i++;
        while (values[j] > values[pivotIdx]) j--;

      if ( i > j ) { break; }

        swap(values[i], values[j]);
        i++;
        if (j != 0) { j--; }
    }

    (*returnVals)[0] = i;
    (*returnVals)[1] = j;

}

template<typename T> void sequentialQuicksort( T values[], unsigned int low, unsigned int high ) {
    if ( low >= high ) { return; }

    PartResults results;
    partition(values, low, high, &results);

    unsigned int i = results[0];
    unsigned int j = results[1];


    sequentialQuicksort( values, low, j );
    sequentialQuicksort( values, i, high );

}





#if defined( TASK )
template<typename T> _Task SortWithTask {
    T *values;
    unsigned int low;
    unsigned int high;
    unsigned int depth;

    void main() {

      if ( low >= high ) { return; }

        if ( depth == 0 ) {
            sequentialQuicksort(values, low, high);

        } else {

            PartResults results;
            partition(values, low, high, &results);
            unsigned int i = results[0];
            unsigned int j = results[1];


            SortWithTask left(values, low, j, depth-1);
            sequentialQuicksort(values, i, high);
        }
    }

  public:
    SortWithTask( T *values, unsigned int low, unsigned int high, unsigned int depth ) : values(values), low(low), high(high), depth(depth) {}
};

#elif defined( ACTOR )

struct SortMsg : public uActor::Message {
    STYPE *values;
    unsigned int low;
    unsigned int high;
    unsigned int depth;

    SortMsg( STYPE *values, unsigned int low, unsigned int high, unsigned int depth ) :
        Message(uActor::Delete), values(values), low(low), high(high), depth(depth) {}
};

_Actor SortWithActor {
    Allocation receive( uActor::Message & msg ) {
        Case( SortMsg, msg ) {
            STYPE *values = msg_d->values;
            unsigned int low = msg_d->low;
            unsigned int high = msg_d->high;
            unsigned int depth = msg_d->depth;

            if ( depth == 0 || low >= high ) { sequentialQuicksort( values, low, high ); } else {

                PartResults results;
                partition(values, low, high, &results);
                unsigned int i = results[0];
                unsigned int j = results[1];
                *new SortWithActor() | *new SortMsg( values, low, j, depth-1 ) | uActor::stopMsg;
                *new SortWithActor() | *new SortMsg( values, i, high, depth-1 ) | uActor::stopMsg;

            }
        } else Case( StopMsg, msg ) return Delete;
        return uActor::Nodelete;
    }


};

#endif


template<typename T> void quicksort( T values[], unsigned int low, unsigned int high, unsigned int depth ) {
    if ( low >= high ) { return; }

    if ( depth == 0 ) {
        sequentialQuicksort( values, low, high );
        return;
    }

#if defined( CBEGIN )
    uThisTask().verify();

    PartResults results;
    partition(values, low, high, &results);
    unsigned int i = results[0];
    unsigned int j = results[1];

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