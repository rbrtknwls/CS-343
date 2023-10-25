#ifndef CS_343_Q3BUFFER_H
#define CS_343_Q3BUFFER_H

#include "BargingCheck.h"
#include <iostream>
#include <vector>
#include <uPRNG.h>

#ifdef BUSY
template<typename T> class BoundedBuffer {
    int numberOfElements = 0;                                           // Stores the number of elements in the buffer
    unsigned long int numberOfBlocks = 0;                               // Stores current number of blocks
    bool poisoned = false;                                              // Bool for if the buffer is poisoned
    int sizeLimit;                                                      // Stores capacity for the buffer

    uOwnerLock buffLock;                                                // Lock for the buffer
    uCondLock prodLock;                                                 // Cond lock to syncronize with producers
    uCondLock consLock;                                                 // Cond lock to syncronize with consumers
    std::vector<T> items;                                               // Stores the elements in the buffer

  public:
    _Event Poison {};                                                   // Exception for poison

    unsigned long int blocks() { return numberOfBlocks; }               // Return the number of times we block
    void poison() { poisoned = true; }                                  // Set the posion state to true

    // Method producers use to insert a value
	void insert( T elem ) {
        buffLock.acquire();                                              // Grab the lock
        try {
            if ( numberOfElements == sizeLimit ) {                       // if we cant add a value, block
                numberOfBlocks++;
                prodLock.wait(buffLock);
            } // if
            items.push_back(elem);                                       // add value to buffer
            numberOfElements++;                                          // update number of elements
            consLock.signal();                                           // signal to consumers
        } _Finally {
            buffLock.release();                                          // release the buffer
        } // try

	} // BoundBuffer::insert

    // Method consumers use to remove a value
	T remove() __attribute__(( warn_unused_result )) {
        buffLock.acquire();                                              // grab the buffer lock
        T elem;                                                          // declare the element to be returned
        try {

            if ( numberOfElements == 0 ) {                               // if we cant remove value, block
                if ( poisoned ) { _Throw Poison(); }
                numberOfBlocks++;
                consLock.wait(buffLock);
            } // if

            elem = items[--numberOfElements];                            // get the last element
            items.pop_back();                                            // pop the element off the list
            prodLock.signal();                                           // get a producer to wake up

        } _Finally {
            buffLock.release();                                          // release the lock
        } // try

        return elem;

	} // BoundedBuffer::remove
    BoundedBuffer( const unsigned int size = 10 ) : sizeLimit(size) {}
};
#endif // BUSY

#ifdef NOBUSY
template<typename T> class BoundedBuffer {
    int numberOfElements = 0;                                            // stores the number of elements in buffer
    unsigned long int numberOfBlocks = 0;                                // stores how many blocks buffer has done
    bool poisoned = false;                                               // stores if buffer is poisoned
    int sizeLimit;                                                       // stores how many values the buffer can store

    uOwnerLock buffLock;                                                 // lock for buffer
    uCondLock prodLock;                                                  // lock for producers
    uCondLock consLock;                                                  // lock for consumers
    uCondLock waitLock;                                                  // lock for bargers/waiters
    std::vector<T> items;                                                // stores items of buffer

    bool consFlag = false;                                               // true if intent is to consume
    bool prodFlag = false;                                               // true if intent is to produce
    bool bargeFlag = false;                                              // true if releasing a barging task

    BCHECK_DECL;
  public:
    _Event Poison {};                                                    // exception to throw if poisoned

    unsigned long int blocks() { return numberOfBlocks; }                // return number of blocks
    void poison() { poisoned = true; }                                   // set the poisoned state to true

    // Method producers use to insert a value
	void insert( T elem ) {
        buffLock.acquire();                                              // grab buffer lock
        try {
            PROD_ENTER;

            if ( bargeFlag || prodFlag || consFlag ) {                   // wait if another intent is defined
                waitLock.wait(buffLock);

                if (waitLock.empty()) bargeFlag = false;                 // if no one waiting, no barging
            } // if

            if ( numberOfElements == sizeLimit ) {                       // if we cant add values, block and signal
                if ( consFlag == false ) { waitLock.signal(); }
                numberOfBlocks++;
                prodLock.wait(buffLock);
            } // if

            INSERT_DONE;
            items.push_back(elem);
            numberOfElements++;

            CONS_SIGNAL( consLock );
            if ( consLock.empty() == false ) {                           // if are waiting to consume
                consFlag = true;
                consLock.signal();
            } else if ( waitLock.empty() == false ) {                    // if there are threads waiting
                bargeFlag = true;
                waitLock.signal();
            } // if
            prodFlag = false;                                             // no longer intent on producing

        } _Finally {
            buffLock.release();
        } // try

	} // BoundedBuffer::insert

	T remove() __attribute__(( warn_unused_result )) {
        buffLock.acquire();                                               // grab the buffer lock
        T elem;                                                           // define the element to return
        try {
            CONS_ENTER;

            if ( bargeFlag || prodFlag || consFlag ) {                    // wait if another intent is defined
                waitLock.wait(buffLock);

                if (waitLock.empty()) bargeFlag = false;                  // if no waiting, cant be barging
            } // if


            if ( numberOfElements == 0 ) {                                // if we cant consume, wait and signal
                if ( prodFlag == false ) { waitLock.signal(); }
                if ( poisoned ) { _Throw Poison(); }

                numberOfBlocks++;
                consLock.wait(buffLock);
            }

            REMOVE_DONE;
            elem = items[--numberOfElements];
            items.pop_back();

            PROD_SIGNAL( prodLock );
            if ( prodLock.empty() == false ) {                             // if lock non empty, set intent and signal
                prodFlag = true;
                prodLock.signal();
            } else if ( waitLock.empty() == false ) {                      // if no producers waiting, release waitlock
                bargeFlag = true;
                waitLock.signal();
            } // if
            consFlag = false;                                              // remove intent

        } _Finally {
            buffLock.release();
        } // try

        return elem;

	}
    BoundedBuffer( const unsigned int size = 10 ) : sizeLimit(size) {}
};
#endif // NOBUSY

_Task Producer {
    BoundedBuffer<int> & buffer;                                           // store reference to buffer
    int produce = 0;
    int delay = 0;

    void main() {
        for ( int i = 0; i < produce; i++ ) {
            yield( prng( delay ) );                                        // delay up to "delay" time
            buffer.insert(i);                                              // insert to buffer
        } // for
    }
  public:
    Producer( BoundedBuffer<int> & buffer, const int produce, const int delay ) : buffer(buffer),
        produce(produce), delay(delay) {}
};

_Task Consumer {

    BoundedBuffer<int> & buffer;                                           // reference to buffer
    int delay = 0;
    int &sum;                                                              // reference to where results go

    void main() {
        try {
            _Enable {
                for ( ;; ) {
                    yield( prng( delay ) );                                // delay for some time
                    int result = buffer.remove();                          // remove from buffer
                    sum += result;
                } // for
            }
        } catch ( BoundedBuffer<int>::Poison &poison ) {
            return;                                                        // results should be updated so exit
        } // try
    }
  public:
    Consumer( BoundedBuffer<int> & buffer, const int delay, int &sum ) : buffer(buffer),
        delay(delay), sum(sum) {}
};

#endif //CS_343_Q3BUFFER_H
