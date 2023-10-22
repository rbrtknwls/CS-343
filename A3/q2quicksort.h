#ifndef CS_343_Q2SORTINGIMPL_H
#define CS_343_Q2SORTINGIMPL_H

#include <iostream>

using namespace std;

template<typename T> int partition ( T values[], unsigned int low, unsigned high ) {
    T pivot = values[low + (high - low) / 2];
    int localSwap = low;

    for ( int j = low; j <= high; j++ ) {
        if ( values[j] < pivot ) {
            T temp = values[j];
            values[j] = values[localSwap];
            values[localSwap] = temp;

            localSwap++;
        }
    }

    localSwap++;

    T temp = values[high];
    values[high] = values[localSwap];
    values[localSwap] = temp;

    return localSwap;

}


template<typename T> void quicksort( T values[], unsigned int low, unsigned int high, unsigned int depth ) {

    int idx = partition(values, low, high);

}



#endif //CS_343_Q2SORTINGIMPL_H
