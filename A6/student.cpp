#include "student.h"

void Student::main() {

}


Student::Student( Printer & prt, WATCardOffice & cardOffice, Groupoff & groupoff,
    unsigned int id, unsigned int maxPurchases ) :
    printer( &prt ), watCardOffice ( &cardOffice ), groupoffer( &groupoff ), localID( id ) {

    printer->print( Printer::Student,  localID, 'S' );

    numberOfPurchases = prng( maxPurchases ) + 1;
    favouriteFlavour = prng( 4 );

    watcard = watCardOffice->create( 0, 5 );
    giftcard = groupoffer->giftCard();

}

Student::~Student() {

    delete watcard();

    printer->print( Printer::Student,  localID, 'F' );
}