#ifndef CS_343_Q2SORTINGIMPL_H
#define CS_343_Q2SORTINGIMPL_H

#include <iostream>

using namespace std;

template<typename T> void swap ( T values[], unsigned int idx1, unsigned int idx2 ) {
    T temp = values[idx1];
    values[idx1] = values[idx2];
    values[idx2] = temp;

}

template<typename T> unsigned int partition ( T values[], unsigned int low, unsigned high ) {

    int pivotIdx = low + (high - low) / 2;

    T pivot = values[pivotIdx];
    unsigned int localSwap = low;

    for ( unsigned int j = low; j < high; j++ ) {
        if ( values[j] < pivot ) {
            T temp = values[localSwap];
            values[localSwap] = values[j];
            values[j] = temp;

            localSwap++;
        }
    }

    T temp = values[localSwap];
    values[localSwap] = values[pivotIdx];
    values[pivotIdx] = temp;

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
