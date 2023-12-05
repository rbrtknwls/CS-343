#include "student.h"
#include "vendingmachine.h"
#include "bottlingplant.h"

// ================== Private Method(s) ==================== //

void Student::main() {

    VendingMachine *machine = nameServer.getMachine( localID );
    BottlingPlant::Flavours flavour = static_cast<BottlingPlant::Flavours>( favouriteFlavour );
    printer->print(Printer::Kind::Student, localID, 'V', machine->getId());

    bool madeAPurchase = true;
    WATCard *payment = nullptr;

    for ( unsigned int currentPurchase = 0; currentPurchase < numberOfPurchases; currentPurchase++ ) {

        if ( madeAPurchase ) { yield( prng( 1, 10 ) ); }

        madeAPurchase = true;

        _Select( giftcard ) {

            try {

                payment = giftcard();
                machine->buy(flavour, *payment);
                printer->print(Printer::Kind::Student, localID, 'G', flavour, payment->getBalance());
                giftcard.reset();
                delete payment;

            } catch( VendingMachine::Free & ) {

                printer->print(Printer::Kind::Student, localID, 'a', flavour, 0);

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
             } catch ( WATCardOffice::Lost &lost ) {
                 watcard = watCardOffice->create( localID, 5 );
                 currentPurchase--;
                 madeAPurchase = false;
                 printer->print( Printer::Student, localID, 'L' );
                 continue;
             }
        }

        /*
        for ( ;; ) {

            try {
                _Select( giftcard ) {
                    payment = giftcard();
                    machine->buy( flavour, *payment );
                    giftcard.reset();
                    useGC = true;
                    printer->print(Printer::Kind::Student, localID, 'G', flavour, payment->getBalance());
                    delete payment;
                    break;
                } or _Select( watcard ) {
                    payment = watcard();
                    machine->buy( flavour, *payment );
                    printer->print(Printer::Kind::Student, localID, 'B', flavour, payment->getBalance());
                    break;
                } // _Select
            } catch (WATCardOffice::Lost &lost) {

                printer->print(Printer::Kind::Student, localID, 'L');
                watcard = watCardOffice->create( localID, 5 );

            } catch(VendingMachine:: Free &) {
                if (useGC) {
                    printer->print(Printer::Kind::Student, localID, 'a', flavour, payment->getBalance());
                } else {
                    printer->print(Printer::Kind::Student, localID, 'A', flavour, payment->getBalance());
                } // if

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

            } // try
        } */

    }

}


// ================== Constructor / Destructor ==================== //


Student::Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff,
    unsigned int id, unsigned int maxPurchases ) :
    printer( &prt ), nameServer(nameServer), watCardOffice ( &cardOffice ), groupoffer( &groupoff ), localID( id ) {


    numberOfPurchases = prng( 1, maxPurchases );
    favouriteFlavour = prng( 4 );

    watcard = watCardOffice->create( localID, 5 );
    giftcard = groupoffer->giftCard();

    printer->print( Printer::Student, localID, 'S', favouriteFlavour, numberOfPurchases );

}

Student::~Student() {
    try {
        delete watcard();
    } catch ( WATCardOffice::Lost & ) { }
    printer->print( Printer::Student, localID, 'F' );
    // try { delete watcard(); } catch ( WATCardOffice::Lost &lost ) {}
}