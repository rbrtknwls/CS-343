#include "groupoff.h"

// ================== Private Member(s) ==================== //

void Groupoff::main() {

    for ( ; currentStudent < numStudents ; currentStudent++ ) {
        //_Accept( giftCard );
    }

    for ( ; currentStudent >= 0 ; currentStudent-- ) {

    }

}

// ================== Public Member(s) ==================== //

WATCard::FWATCard Groupoff::giftCard() {
    return giftCards[currentStudent];
}

// ================== Constructor / Destructor ==================== //

Groupoff::Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay ) :
    printer( &prt ), numStudents( (int) numStudents ), sodaCost( sodaCost ), groupoffDelay(groupoffDelay) {

    currentStudent = 0;
    giftCards = new WATCard::FWATCard[numStudents];
    printer->print( Printer::Groupoff, 'S' );
}

Groupoff::~Groupoff() {

    printer->print( Printer::Groupoff, 'F' );

}
