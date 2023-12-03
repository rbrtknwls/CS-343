#include "student.h"

void Student::main() {

    for ( unsigned int currentPurchase; currentPurchase < maxPurchases; currentPurchase ) {
        yield( prng( 10 ) + 1 );

        _Select( giftcard ) {

        } or  _Select( watcard ) {
            
        }
    }

}


Student::Student( Printer & prt, WATCardOffice & cardOffice, Groupoff & groupoff,
    unsigned int id, unsigned int maxPurchases ) :
    printer( &prt ), watCardOffice ( &cardOffice ), groupoffer( &groupoff ), localID( id ) {

    printer->print( Printer::Student, localID, 'S' );

    numberOfPurchases = prng( maxPurchases ) + 1;
    favouriteFlavour = prng( 4 );

    watcard = watCardOffice->create( 0, 5 );
    giftcard = groupoffer->giftCard();

}

Student::~Student() {
    printer->print( Printer::Student, localID, 'F' );
    delete watcard();

}