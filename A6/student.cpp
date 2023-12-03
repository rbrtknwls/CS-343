#include "student.h"

void Student::main() {

    bool madeAPurchase = true;
    for ( unsigned int currentPurchase = 0; currentPurchase < numberOfPurchases; currentPurchase++ ) {
        if ( madeAPurchase ) { yield( prng( 10 ) + 1 ); }

        madeAPurchase = true;

        WATCard *payment;
        _Select( giftcard ) {

        } or  _Select( watcard ) {

            try {
                payment = watcard();
            } catch ( WATCardOffice::Lost &lost ) {
                watcard = watCardOffice->create( 0, 5 );
                currentPurchase--;
                madeAPurchase = false;
                printer->print( Printer::Student, localID, 'L' );
                continue;
            }

        }
    }

}


Student::Student( Printer & prt, WATCardOffice & cardOffice, Groupoff & groupoff,
    unsigned int id, unsigned int maxPurchases ) :
    printer( &prt ), watCardOffice ( &cardOffice ), groupoffer( &groupoff ), localID( id ) {


    numberOfPurchases = prng( maxPurchases ) + 1;
    favouriteFlavour = prng( 4 );

    watcard = watCardOffice->create( 0, 5 );
    giftcard = groupoffer->giftCard();

    printer->print( Printer::Student, localID, 'S', favouriteFlavour, numberOfPurchases );

}

Student::~Student() {
    printer->print( Printer::Student, localID, 'F' );
    try { delete watcard(); } catch ( WATCardOffice::Lost &lost ) {}

}