#ifndef CS_343_Q2SORTINGIMPL_H
#define CS_343_Q2SORTINGIMPL_H

#include <iostream>
#include <uCobegin.h>

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


template<typename T> void quicksort( T values[], int low, int high, int depth ) {
  if (low >= high) { return; }

    int idx = partition(values, low, high);

    if ( depth == 0 ) {
#if defined( CBEGIN )
        quicksort(values, low, idx - 1, depth);
        quicksort(values, idx + 1, high, depth);
#endif
    } else {
#if defined( CBEGIN )
        COBEGIN
            BEGIN quicksort(values, low, idx - 1, depth-1); END
            BEGIN quicksort(values, idx + 1, high, depth-1); END
        COEND
#endif
    }
}





#endif //CS_343_Q2SORTINGIMPL_H
