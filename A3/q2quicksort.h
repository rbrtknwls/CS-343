#ifndef CS_343_Q2SORTINGIMPL_H
#define CS_343_Q2SORTINGIMPL_H

#include <iostream>

using namespace std;

template<typename T> int partition ( T values[], unsigned int low, unsigned high ) {

    T pivot = values[low + (high - low) / 2];

    cout << pivot << endl;

    return low;

}


template<typename T> void quicksort( T values[], unsigned int low, unsigned int high, unsigned int depth ) {
    partition(values, low, high);
}



#endif //CS_343_Q2SORTINGIMPL_H
