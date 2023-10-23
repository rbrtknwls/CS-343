//
// Created by robde on 2023/10/23.
//

#ifndef CS_343_Q3BUFFER_H
#define CS_343_Q3BUFFER_H


#ifdef BUSY							// busy waiting implementation
// implementation
#endif // BUSY

#ifdef NOBUSY
#include "BargingCheck.h"
template<typename T> class BoundedBuffer {

  public:
    _Event Poison {} {

    }
    BoundedBuffer( const unsigned int size = 10 ) {

    }
    unsigned long int blocks() {

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
