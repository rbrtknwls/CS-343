#include "student.h"
#include "vendingmachine.h"

#include <iostream>


// ================== Private Method(s) ==================== //


void Student::main() {

    // Get a machine for this student
    VendingMachine *machine = nameServer.getMachine( localID );

    printer->print(Printer::Kind::Student, localID, 'V', machine->getId());

    bool madeAPurchase = true;                    // Store if we made a purchase
    WATCard *payment = nullptr;                   // Store our method of paying

    for ( unsigned int currentPurchase = 0; currentPurchase < numberOfPurchases; currentPurchase++ ) {

        if ( madeAPurchase ) { yield( prng( 1, 10 ) ); }
        madeAPurchase = true;

        _Select( giftcard ) {

            try {

                payment = giftcard();
                machine->buy(flavour, payment);

                printer->print(Printer::Kind::Student, localID, 'G', flavour, payment->getBalance());

                giftcard.reset();
                delete payment;

            } catch( VendingMachine::Free & ) {

                printer->print(Printer::Kind::Student, localID, 'a', flavour, payment->getBalance());

                if (prng(2) == 1) {
                    yield(4);
                } else {
                    printer->print(Printer::Kind::Student, localID, 'X');
                }
                madeAPurchase = false;

            } catch ( VendingMachine::Stock & ) {

                machine = nameServer.getMachine( localID );
                printer->print( Printer::Kind::Student, localID, 'V', machine->getId() );
                madeAPurchase = false;

            }

        } or _Select( watcard ) {

             try {
                 payment = watcard();
                 machine->buy( flavour, payment );

                 printer->print(Printer::Kind::Student, localID, 'B', flavour, payment->getBalance());
                 break;

             } catch ( WATCardOffice::Lost &lost ) {
                 watcard = watCardOffice->create( localID, 5 );
                 currentPurchase--;
                 madeAPurchase = false;
                 printer->print( Printer::Student, localID, 'L' );
                 continue;

             } catch(VendingMachine:: Free &) {
                 printer->print(Printer::Kind::Student, localID, 'A', flavour, payment->getBalance());

                 if (prng(2) == 1) {
                     yield(4);
                 } else {
                     printer->print(Printer::Kind::Student, localID, 'X');
                 }
             } catch( VendingMachine::Funds & ) {
                 watcard = watCardOffice->transfer(localID, machine->cost() + 5, payment);

             } catch( VendingMachine::Stock & ) {
                 machine = nameServer.getMachine(localID);
                 printer->print(Printer::Kind::Student, localID, 'V', machine->getId());

             }
        }

    }

}


// ================== Constructor / Destructor ==================== //


Student::Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff,
    unsigned int id, unsigned int maxPurchases ) :
    printer( &prt ), nameServer(nameServer), watCardOffice ( &cardOffice ), groupoffer( &groupoff ), localID( id ) {


    numberOfPurchases = prng( 1, maxPurchases );
    unsigned int favouriteFlavour = prng( 4 );


    watcard = watCardOffice->create( localID, 5 );
    giftcard = groupoffer->giftCard();

    printer->print( Printer::Student, localID, 'S', favouriteFlavour, numberOfPurchases );
    BottlingPlant::Flavours flavour = static_cast<BottlingPlant::Flavours>( favouriteFlavour );

}

Student::~Student() {
    try {
        delete watcard();
    } catch ( WATCardOffice::Lost & ) { }
    printer->print( Printer::Student, localID, 'F' );
    // try { delete watcard(); } catch ( WATCardOffice::Lost &lost ) {}
}