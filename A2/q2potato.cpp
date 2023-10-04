#include <uPRNG.h>
#include <iostream>

#include "q2potato.h"

using namespace std;

/*
 * Helper function to help print the number of ticks, if current ticks are 1 the output is different then if ticks
 *    are any other kind of value.
 */
void printPotatoTicks( int currentTicks ) {
    cout << "  POTATO goes off after " << currentTicks << " tick";
    if ( currentTicks != 1 ) { cout << "s"; }
    cout << endl;
}

/*
 *  This is the main constructor for potato, it should run at the start of every game.
 *    We will set the current ticks to be the same as maxTicks and output to cout how
 *    long it will take the potato to explode
 */
Potato::Potato( PRNG &prng, unsigned int maxTicks ) : prng( prng ) {
    currentTicks = prng(1, maxTicks);
    printPotatoTicks( currentTicks );
}


/*
 *  We run this code right after the potato explodes, acts similar to the constructor except
 *    we dont need to set a prng.
 */
void Potato::reset(unsigned int maxTicks) {
    currentTicks = prng(1, maxTicks);
    printPotatoTicks( currentTicks );
}

/*
 *  This is the code that decreases currentTicks, if the potato is going to explode then we throw an
 *    exception which will be caught by one of the players. Otherwise we just decrease the current
 *    number of ticks
 */
void Potato::countdown() {
    if (--currentTicks == 0) {
        throw Explode();
    }
}