#include "groupoff.h"

using namespace std;

// ================== Private Member(s) ==================== //

void Groupoff::main() {

    for ( ; currentStudent < numStudents ; currentStudent++ ) {
        _Accept( giftCard );
    }

    for ( ; currentStudent > 0 ; currentStudent-- ) {
        _Accept ( ~Groupoff ) { break; }
        _Else{

            yield(groupoffDelay);

            printer->print( Printer::Groupoff, 'D', sodaCost );
            unsigned int studentToPick = prng( currentStudent );

            WATCard * giftCard = new WATCard();
            giftCard->deposit( sodaCost );
            giftCards[studentToPick].delivery( giftCard );


            swap( giftCards[studentToPick], giftCards[currentStudent-1] );

        }
    }
}

// ================== Public Member(s) ==================== //

WATCard::FWATCard Groupoff::giftCard() {
    return giftCards[currentStudent];
}

// ================== Constructor / Destructor ==================== //

Groupoff::Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay ) :
    printer( &prt ), numStudents( (int) numStudents ), sodaCost( sodaCost ), groupoffDelay( groupoffDelay ) {

    currentStudent = 0;
    giftCards = new WATCard::FWATCard[numStudents];
    printer->print( Printer::Groupoff, 'S' );
}

Groupoff::~Groupoff() {

    for ( int student = 0; student < numStudents; student++ ) {
        if ( giftCards[student].available() ) {
            delete giftCards[student]();
        }
    }

    delete[] giftCards;
    printer->print( Printer::Groupoff, 'F' );

}
