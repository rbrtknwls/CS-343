#include "groupoff.h"

using namespace std;

// ================== Private Member(s) ==================== //


/* Main member for group offer, will wait until all the students call giftcard().
 * after it unblocks it will select a random student to fulfill their gift card.
 */

void Groupoff::main() {


    for ( ; currentStudent < numStudents ; currentStudent++ ) {        // Wait for all the students to call gift card
        _Accept( giftCard );
    } // for

    for ( ; currentStudent > 0 ; currentStudent-- ) {                  // Loop through all students
        _Accept ( ~Groupoff ) { break; }                               // If destructor is called, exit
        _Else{

            yield( groupoffDelay );                                    // wait group delay

            printer->print( Printer::Groupoff, 'D', sodaCost );
            unsigned int studentToPick = prng( currentStudent );       // pick a random student

            WATCard * giftCard = new WATCard();                        // make a watcard
            giftCard->deposit( sodaCost );
            giftCards[studentToPick].delivery( giftCard );

            // Move future to "back" wont be considered for getting a new gift card
            swap( giftCards[studentToPick], giftCards[currentStudent-1] );

        } // _Accept
    } // for

}

// ================== Public Member(s) ==================== //

// Mutex member for getting a gift card
WATCard::FWATCard Groupoff::giftCard() {
    return giftCards[currentStudent];
}

// ================== Constructor / Destructor ==================== //

Groupoff::Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay ) :
    printer( &prt ), numStudents( (int) numStudents ), sodaCost( sodaCost ), groupoffDelay( groupoffDelay ) {

    currentStudent = 0;
    giftCards = new WATCard::FWATCard[numStudents];                      // Create an array of future gift cards
    printer->print( Printer::Groupoff, 'S' );
}

Groupoff::~Groupoff() {

    for ( int student = 0; student < numStudents; student++ ) {
        if ( giftCards[student].available() ) {                          // If gift card is unused at this point
            delete giftCards[student]();                                 // delete it (student has ended before this)
        }
    }

    delete[] giftCards;
    
    printer->print( Printer::Groupoff, 'F' );

}
