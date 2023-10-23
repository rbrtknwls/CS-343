#ifndef CS_343_Q3BUFFER_H
#define CS_343_Q3BUFFER_H

#include "BargingCheck.h"
#include <iostream>


#ifdef BUSY							// busy waiting implementation
// implementation
#endif // BUSY

#ifdef NOBUSY
template<typename T> class BoundedBuffer {
    int blocks = 0;
  public:
    _Event Poison {};
    BoundedBuffer( const unsigned int size = 10 ) {

    }
    unsigned long int blocks() {
        return blocks;
    }
    void poison() {

    }
	void insert( T elem ) {

	}
	T remove() __attribute__(( warn_unused_result )) {

	}
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
