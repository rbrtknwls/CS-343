#ifndef CS_343_Q3BUFFER_H
#define CS_343_Q3BUFFER_H

#include "BargingCheck.h"
#include <iostream>
#include <vector>

#ifdef BUSY
template<typename T> class BoundedBuffer {
    int numberOfBlocks = 0;
    std::vector<T> items;
    int size = 0;
    int numberOfElements = 0;

  public:
    _Event Poison {};

    unsigned long int blocks() {
        return numberOfBlocks;
    }
    void poison() {

    }
	void insert( T elem ) {

        items.push_back(elem);


	}
	T remove() __attribute__(( warn_unused_result )) {

        T elem = items[items.size() - 1]
        items.pop_back();

        return elem;

	}
    BoundedBuffer( const unsigned int size = 10 ) : size(size) {}
};
#endif // BUSY

#ifdef NOBUSY
template<typename T> class BoundedBuffer {
    int numberOfBlocks = 0;
    std::vector<int> items;
    int size = 0;
  public:
    _Event Poison {};

    unsigned long int blocks() {
        return numberOfBlocks;
    }
    void poison() {

    }
	void insert( T elem ) {

	}
	T remove() __attribute__(( warn_unused_result )) {

	}
    BoundedBuffer( const unsigned int size = 10 ) : size(size) {}
};
#endif // NOBUSY

_Task Producer {
      void main();
    public:
      Producer( BoundedBuffer<int> & buffer, const int Produce, const int Delay );
};

_Task Consumer {
    void main();
  public:
    Consumer( BoundedBuffer<int> & buffer, const int Delay, int &sum );
};

#endif //CS_343_Q3BUFFER_H
