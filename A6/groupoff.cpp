#include "groupoff.h"

// ================== Private Member(s) ==================== //

void Groupoff::main() {

}

// ================== Public Member(s) ==================== //

WATCard::FWATCard Groupoff::giftCard() {

}

// ================== Constructor / Destructor ==================== //

Groupoff::Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay ) :
    printer( prt ), numStudents( numStudents ), sodaCost( sodaCost ), groupoffDelay(groupoffDelay) {

    printer->print( Printer::Groupoff, "S");
}

Groupoff::~Groupoff() {

    printer->print( Printer::Groupoff, "F");

}
