#include "student.h"

void Student::main() {

}


Student::Student( Printer & prt, WATCardOffice & cardOffice, Groupoff & groupoff,
    unsigned int id, unsigned int maxPurchases ) :
    printer( &prt ), watCardOffice ( &cardOffice ), groupoff( &groupoff ), localID( id ) {

    printer->print( Printer::WATCardOffice,  localID, 'S' );

    numberOfPurchases = prng( maxPurchases ) + 1;
    favouriteFlavour = prng( 4 );

    watcard = watCardOffice->create(0, 5);
    giftcard = groupoff->giftCard();

}

Student::~Student() {

    delete watcard();

    printer->print( Printer::WATCardOffice,  localID, 'F' );
}