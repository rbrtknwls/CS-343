#include "student.h"
#include "vendingmachine.h"
#include "bottlingplant.h"

#include <iostream>


// ================== Private Method(s) ==================== //


void Student::main() {

    // Get a machine for this student
    VendingMachine *machine = nameServer.getMachine( localID );
    BottlingPlant::Flavours flavour = static_cast<BottlingPlant::Flavours>( favouriteFlavour );

    printer->print(Printer::Kind::Student, localID, 'V', machine->getId());

    WATCard *payment = nullptr;                           // Store our method of paying
    yield( prng( 1, 10 ) );                               // Yield on the first purchase
    for ( unsigned int currentPurchase = 0; currentPurchase < numberOfPurchases; currentPurchase++ ) {

        _Select( giftcard ) {                             // Buy if giftcard is created

            try {
                payment = giftcard();                     // Grab the giftcard
                machine->buy( flavour, payment );         // Try to buy (Can throw!)

                printer->print(Printer::Kind::Student, localID, 'G', flavour, payment->getBalance());

                giftcard.reset();                         // Reset the future
                delete payment;                           // Delete Watcard

                yield( prng( 1, 10 ) );                   // Made purchase so yield

            // Catch if the vending machine gives us a free drink
            } catch( VendingMachine::Free & ) {

                printer->print(Printer::Kind::Student, localID, 'a', flavour, payment->getBalance());

                if ( prng(2) == 1 ) {                     // Watch the ad
                    yield(4);
                } else {                                  // Does not watch the ad
                    printer->print(Printer::Kind::Student, localID, 'X');
                }

            // Catch if the vending machine is out of stuck
            } catch ( VendingMachine::Stock & ) {

                // Get a new machine
                machine = nameServer.getMachine( localID );
                printer->print( Printer::Kind::Student, localID, 'V', machine->getId() );

            }

        } or _Select( watcard ) {                          // Try to buy using a watcard

             try {
                 payment = watcard();                      // Get watcard (can throw!)
                 machine->buy( flavour, payment );         // Try to buy (can throw!)

                 printer->print(Printer::Kind::Student, localID, 'B', flavour, payment->getBalance());
                 yield( prng( 1, 10 ) );                   // Made purchase so must yield

             // Catch if the watcard was lost in transit
             } catch ( WATCardOffice::Lost &lost ) {
                 // Make a new watCard
                 watcard = watCardOffice->create( localID, 5 );
                 currentPurchase--;
                 printer->print( Printer::Student, localID, 'L' );
                 continue;

             // Catch if the vending machine gives us a free drink
             } catch( VendingMachine:: Free & ) {
                 printer->print(Printer::Kind::Student, localID, 'A', flavour, payment->getBalance());

                 if ( prng(2) == 1 ) {                      // Watch ad 50% of the time
                     yield(4);
                 } else {
                     printer->print(Printer::Kind::Student, localID, 'X');
                 }

             // Catch if the vending machine requires new funds
             } catch( VendingMachine::Funds & ) {
                 watcard = watCardOffice->transfer(localID, machine->cost() + 5, payment);

             // Catch if the vending machine is out of stock
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


    numberOfPurchases = prng( 1, maxPurchases );                     // Get number of purchases to make [1,max)
    favouriteFlavour = prng( 4 );                                    // Get flavour to look for [0,3]

    watcard = watCardOffice->create( localID, 5 );                   // Create watcard
    giftcard = groupoffer->giftCard();                               // Create giftcard

    printer->print( Printer::Student, localID, 'S', favouriteFlavour, numberOfPurchases );

}

Student::~Student() {
    try { delete watcard(); } catch ( WATCardOffice::Lost & ) { }    // If not lost, delete
    printer->print( Printer::Student, localID, 'F' );
}