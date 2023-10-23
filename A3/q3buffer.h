#ifndef CS_343_Q3BUFFER_H
#define CS_343_Q3BUFFER_H

#include "BargingCheck.h"
#include <iostream>
#include <vector>
#include <uPRNG.h>

#ifdef BUSY
template<typename T> class BoundedBuffer {
    int sizeLimit;
    int numberOfBlocks = 0;
    int numberOfElements = 0;

    std::vector<T> items;

  public:
    _Event Poison {};

    unsigned long int blocks() {
        return numberOfBlocks;
    }
    void poison() {

    }
	void insert( T elem ) {

        if ( numberOfElements == sizeLimit ) {}
        items.push_back(elem);
        numberOfElements++;


	}
	T remove() __attribute__(( warn_unused_result )) {

        if ( numberOfElements == 0 ) {}
        T elem = items[--numberOfElements];
        items.pop_back();

        return elem;

	}
    BoundedBuffer( const unsigned int size = 10 ) : sizeLimit(size) {}
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
    BoundedBuffer<int> & buffer;
    int produce = 0;
    int delay = 0;

    void main() {
        for ( int i = 0; i < produce; i++ ) {
            yield( prng( delay ) );
            buffer.insert(i);
        }
    }
  public:
    Producer( BoundedBuffer<int> & buffer, const int produce, const int delay ) : buffer(buffer),
        produce(produce), delay(delay) {}
};

_Task Consumer {
    BoundedBuffer<int> & buffer;
    int delay = 0;
    int &sum;

    void main() {
        for ( ;; ) {
            yield( prng( delay ) );
            std::cout << "read some vals";
            int result = buffer.remove();
            sum += result;
        }
    }
  public:
    Consumer( BoundedBuffer<int> & buffer, const int delay, int &sum ) : buffer(buffer),
        delay(delay), sum(sum) {}
};

#endif //CS_343_Q3BUFFER_H
