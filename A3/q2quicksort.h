#ifndef CS_343_Q2SORTINGIMPL_H
#define CS_343_Q2SORTINGIMPL_H

#include <iostream>
#include <uCobegin.h>
#include <uActor.h>

using namespace std;


#if defined( CBEGIN )
template<typename T> void quicksort( T values[], unsigned int low, unsigned int high, unsigned int depth ) {
  if (low >= high || high == (unsigned int)-1) { return; }

    unsigned int pivotIdx = low + (high - low) / 2;
    unsigned int idx = low;

    swap(values[pivotIdx], values[high]);
    for ( unsigned int j = low; j <= high; j++ ) {
        if ( values[j] < values[high] ) {
            swap(values[idx++], values[j]);
        }
    }
    swap(values[idx++], values[high]);


    if ( depth == 0 ) {
        if ( low < idx - 1 ) quicksort( values, low, idx - 1, 0 );
        if ( high < idx + 1) quicksort( values, idx + 1, high, 0 );
    } else {

        COBEGIN
            BEGIN if ( low < idx - 1 ) quicksort( values, low, idx - 1, depth-1 ); END
            BEGIN if ( high < idx + 1) quicksort( values, idx + 1, high, depth-1 ); END
        COEND

    }
}

#elif defined( TASK )
template<typename T> _Task SortWithTask {
    T *values;
    unsigned int low;
    unsigned int high;
    unsigned int depth;

    void main() {

      if ( low >= high ) { return; }

        if ( depth == 0 ) {
            std::cout << "seq start" << endl;
            sequentialQuicksort(values, low, high);
        } else {
            unsigned int idx = partition(values, low, high);
            if ( idx - 1 > 0 ) {
                SortWithTask left(values, low, idx - 1, depth-1);
            }
            sequentialQuicksort(values, idx + 1, high);
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
            unsigned int low = msg_d->low;
            unsigned int high = msg_d->high;
            unsigned int depth = msg_d->depth;



            if ( depth == 0 || low >= high ) { sequentialQuicksort( msg_d->values, low, high ); } else {

                unsigned int idx = partition(msg_d->values, low, high);
                if ( idx - 1 > 0 ) {
                    *new SortWithActor() | *new SortMsg( msg_d->values, low, idx - 1, depth-1 ) | uActor::stopMsg;
                }
                *new SortWithActor() | *new SortMsg( msg_d->values, idx + 1, high, depth-1 ) | uActor::stopMsg;


            }
        } else Case( StopMsg, msg ) return Delete;
        return uActor::Nodelete;
    }


};

#endif





#endif //CS_343_Q2SORTINGIMPL_H