#ifndef CS_343_Q2SORTINGIMPL_H
#define CS_343_Q2SORTINGIMPL_H

#include <iostream>
#include <uCobegin.h>
#include <uActor.h>
#include <bits/stdc++.h>

using namespace std;

template<typename T>
void quicksort( T values[], unsigned int low, unsigned int high, unsigned int depth ) {
    if (low < high) {

        int pivotIdx = low + (high - low) / 2;
        unsigned int localSwap = low;

        swap(values, pivotIdx, high);
        for ( unsigned int j = low; j < high; j++ ) {
            if ( values[j] < values[high] ) {
                swap(values, localSwap++, j);
            }
        }
        swap(values, localSwap, high);


        quicksort(values, low, localSwap - 1, depth);
        quicksort(values, localSwap + 1, high, depth);
    }
}

/*
template<typename T> void sequentialQuicksort( T &values, int low, int high ) {
    if (high == (unsigned int)-1) return;
  if (low < high) {

      int pivotIdx = low + (high - low) / 2;
      unsigned int localSwap = low;

      swap(values[pivotIdx], values[high]);
      for (unsigned int j = low; j < high; j++) {
          if (values[j] < values[high]) {
              swap(values[localSwap++], values[j]);
          }
      }
      swap(values[localSwap], values[high]);

      sequentialQuicksort(values, low, localSwap - 1);
      sequentialQuicksort(values, localSwap + 1, high);
  }
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
    SortWithTask( T *values, int low, int high, int depth ) : values(values), low(low), high(high), depth(depth) {}
};
*/
#if defined( ACTOR )

struct SortMsg : public uActor::Message {
    STYPE *values;
    int low;
    int high;
    int depth;

    SortMsg( STYPE *values, int low, int high, int depth ) :
        Message(uActor::Delete), values(values), low(low), high(high), depth(depth) {}
};

_Actor SortWithActor {
    Allocation receive( uActor::Message & msg ) {
        Case( SortMsg, msg ) {
            int low = msg_d->low;
            int high = msg_d->high;
            int depth = msg_d->depth;



            if ( depth == 0 || low >= high ) { sequentialQuicksort( msg_d->values, low, high ); } else {

                int idx = partition(msg_d->values, low, high);

                *new SortWithActor() | *new SortMsg( msg_d->values, low, idx - 1, depth-1 ) | uActor::stopMsg;
                *new SortWithActor() | *new SortMsg( msg_d->values, idx + 1, high, depth-1 ) | uActor::stopMsg;


            }
        } else Case( StopMsg, msg ) return Delete;
        return uActor::Nodelete;
    }


};



/*
template<typename T> void quicksort( T *values, int low, int high, int depth ) {
  if (low >= high) { return; }


#if defined( CBEGIN )

    if ( depth == 0 ) { sequentialQuicksort(values, low, high); } else {

        int idx = partition(values, low, high);
        COBEGIN
            BEGIN quicksort( values, low, idx - 1, depth-1 ); END
            BEGIN quicksort( values, idx + 1, high, depth-1 ); END
        COEND
    }

#elif defined( TASK )

        SortWithTask sort( values, low, high, depth );

#elif defined( ACTOR )

        uActor::start();
        *new SortWithActor() | *new SortMsg( values, low, high, depth ) | uActor::stopMsg;
        uActor::stop();
*/
#endif





#endif //CS_343_Q2SORTINGIMPL_H
