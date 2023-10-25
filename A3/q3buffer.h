#ifndef CS_343_Q3BUFFER_H
#define CS_343_Q3BUFFER_H

#include "BargingCheck.h"
#include <iostream>
#include <vector>
#include <uPRNG.h>

#ifdef BUSY
template<typename T> class BoundedBuffer {
    int numberOfElements = 0;
    unsigned long int numberOfBlocks = 0;
    bool poisoned = false;
    int sizeLimit;

    uOwnerLock buffLock;
    uCondLock prodLock;
    uCondLock consLock;
    std::vector<T> items;

  public:
    _Event Poison {};

    unsigned long int blocks() {
        return numberOfBlocks;
    }
    void poison() {
        poisoned = true;
    }
	void insert( T elem ) {
        buffLock.acquire();
        try {

            if ( numberOfElements == sizeLimit ) {
                numberOfBlocks++;
                prodLock.wait(buffLock);
            }
            items.push_back(elem);
            numberOfElements++;
            consLock.signal();
        } _Finally {
            buffLock.release();
        }

	}
	T remove() __attribute__(( warn_unused_result )) {
        buffLock.acquire();
        T elem;
        try {

            if ( numberOfElements == 0 ) {
                if ( poisoned ) {
                    _Throw Poison();
                }
                numberOfBlocks++;
                consLock.wait(buffLock);
            }

            elem = items[--numberOfElements];
            items.pop_back();
            prodLock.signal();


        } _Finally {
            buffLock.release();
        }

        return elem;

	}
    BoundedBuffer( const unsigned int size = 10 ) : sizeLimit(size) {}
};
#endif // BUSY

#ifdef NOBUSY
template<typename T> class BoundedBuffer {
    int numberOfElements = 0;
    unsigned long int numberOfBlocks = 0;
    bool poisoned = false;
    int sizeLimit;

    uOwnerLock buffLock;
    uCondLock prodLock;
    uCondLock consLock;
    uCondLock waitLock;
    std::vector<T> items;

    bool consFlag = false;
    bool prodFlag = false;
    bool bargeFlag = false;

    BCHECK_DECL;
  public:
    _Event Poison {};

    unsigned long int blocks() {
        return numberOfBlocks;
    }

    void poison() {
        poisoned = true;
    }

	void insert( T elem ) {
        buffLock.acquire();
        try {
            PROD_ENTER;

            if ( bargeFlag || prodFlag || consFlag ) {
                waitLock.wait(buffLock);

                if (waitLock.empty()) bargeFlag = false;
            }

            if ( numberOfElements == sizeLimit ) {
                if ( consFlag == false && waitLock.empty == false ) { waitLock.signal(); }
                numberOfBlocks++;
                prodLock.wait(buffLock);
            }

            INSERT_DONE;
            items.push_back(elem);
            numberOfElements++;

            CONS_SIGNAL( consLock );
            if ( consLock.empty() == false ) {
                consFlag = true;
                consLock.signal();
            } else if ( waitLock.empty() == false ) {
                bargeFlag = true;
                waitLock.signal();
            }
            prodFlag = false;

        } _Finally {
            buffLock.release();
        }

	}
	T remove() __attribute__(( warn_unused_result )) {
        buffLock.acquire();
        T elem;
        try {

            CONS_ENTER;

            if ( bargeFlag || prodFlag || consFlag ) {
                waitLock.wait(buffLock);

                if (waitLock.empty()) bargeFlag = false;
            }


            if ( numberOfElements == 0 ) {
                if ( prodFlag == false && waitLock.empty == false ) { waitLock.signal(); }
                if ( poisoned ) { _Throw Poison(); }

                numberOfBlocks++;
                consLock.wait(buffLock);
            }

            REMOVE_DONE;
            elem = items[--numberOfElements];
            items.pop_back();

            PROD_SIGNAL( prodLock );
            prodLock.signal();
            if ( prodLock.empty() == false ) {
                prodFlag = true;
                prodLock.signal();
            } else if ( waitLock.empty() == false ) {
                bargeFlag = true;
                waitLock.signal();
            }
            consFlag = false;

        } _Finally {
            buffLock.release();
        }

        return elem;

	}
    BoundedBuffer( const unsigned int size = 10 ) : sizeLimit(size) {}
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
        try {
            _Enable {
                for ( ;; ) {

                    yield( prng( delay ) );
                    int result = buffer.remove();
                    sum += result;

                }
            }
        } catch ( BoundedBuffer<int>::Poison &poison ) {
            return;
        }
    }
  public:
    Consumer( BoundedBuffer<int> & buffer, const int delay, int &sum ) : buffer(buffer),
        delay(delay), sum(sum) {}
};

#endif //CS_343_Q3BUFFER_H
