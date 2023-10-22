#ifndef CS_343_Q2SORTINGIMPL_H
#define CS_343_Q2SORTINGIMPL_H

#include <iostream>
#include <uCobegin.h>
#include <uActor.h>

using namespace std;

template<typename T> void swap ( T values[], unsigned int idx1, unsigned int idx2 ) {
    T temp = values[idx1];
    values[idx1] = values[idx2];
    values[idx2] = temp;
}

template<typename T> unsigned int partition ( T values[], unsigned int low, unsigned int high ) {
    int pivotIdx = low + (high - low) / 2;
    unsigned int localSwap = low;

    swap(values, pivotIdx, high);
    for ( unsigned int j = low; j < high; j++ ) {
        if ( values[j] < values[high] ) {
            swap(values, localSwap++, j);
        }
    }
    swap(values, localSwap, high);

    return localSwap;
}

template<typename T> void sequentialQuicksort( T values[], int low, int high ) {
  if (low >= high) { return; }

    int idx = partition(values, low, high);

    sequentialQuicksort(values, low, idx - 1);
    sequentialQuicksort(values, idx + 1, high);

}

#if defined( TASK )
template<typename T> _Task SortWithTask {
    T *values;
    int low;
    int high;
    int depth;

    void main() {

      if ( low >= high ) { return; }

        if ( depth == 0 ) { sequentialQuicksort(values, low, high); } else {
            int idx = partition(values, low, high);
            SortWithTask left(values, low, idx - 1, depth-1);
            sequentialQuicksort(values, idx + 1, high);
        }
    }

  public:
    SortWithTask( T values[], int low, int high, int depth ) : values(values), low(low), high(high), depth(depth) {}
};
#elif defined( ACTOR )

struct SortMsg : public uActor::Message {
    T *values;
    int low;
    int high;
    int depth;

    SortMsg( T values[], int low, int high, int depth ) : Message( uActor::Delete ),
        values(values), low(low), high(high), depth(depth) {}
};

_Actor SortWithActor {
    Allocation receive( Message & msg ) {
        Case( StrMsg, msg ) {
            if ( depth == 0 ) { sequentialQuicksort(values, low, high); } else {

                int idx = partition(msg->values, msg->low, msg->high);

            }


        } else Case( StopMsg, msg ) return Delete;
    }

};
#endif


template<typename T> void quicksort( T values[], int low, int high, int depth ) {
  if (low >= high) { return; }

    if ( depth == 0 ) { sequentialQuicksort(values, low, high); } else {

#if defined( CBEGIN )
        int idx = partition(values, low, high);

        COBEGIN
            BEGIN quicksort(values, low, idx - 1, depth-1); END
            BEGIN quicksort(values, idx + 1, high, depth-1); END
        COEND
#elif defined( TASK )
        SortWithTask sort(values, low, high, depth);
#endif
    }
}




#endif //CS_343_Q2SORTINGIMPL_H
