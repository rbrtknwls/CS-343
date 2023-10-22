#ifndef CS_343_Q2SORTINGIMPL_H
#define CS_343_Q2SORTINGIMPL_H

#include <iostream>

using namespace std;

template<typename T> unsigned int partition ( T values[], unsigned int low, unsigned high ) {
    T pivot = values[low + (high - low) / 2];
    unsigned int localSwap = low;

    for ( unsigned int j = low; j <= high; j++ ) {
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

    if (low < high) {

        int idx = partition(values, low, high);

        quicksort(values, low, idx - 1, depth);
        quicksort(values, idx + 1, high, depth);
        
    }


}



#endif //CS_343_Q2SORTINGIMPL_H
