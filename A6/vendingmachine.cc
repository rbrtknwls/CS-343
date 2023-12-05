#include "vendingmachine.h"
#include "printer.h"
#include "nameserver.h"
#include "watCard.h"


void VendingMachine::main() {

    nameServer->VMregister(this);

    LOOP: for( ;; ) {

        try {
            _Accept( ~VendingMachine ) {                      // Accept destructor and break out of main
                break;

            } or _Accept( buy ) {                             // Accept buying a soda
                VMCard->withdraw( sodaCost );                 // Withdraw money from the card
                stock[currFlavour]--;                         // Reduce stock of that flavour
                printer->print( Printer::Kind::Vending, id, 'B', currFlavour, stock[currFlavour] );
                wait.signalBlock();                           // Allow task to finish

            } or _Accept( inventory ) {                       // Accept request for inventory
                printer->print( Printer::Kind::Vending, id, 'r' );
                _Accept( restocked ) {                        // Wait for restock to happen
                    printer->print( Printer::Kind::Vending, id, 'R' );
                } // _Accept
            } // _Accept

        } catch ( uMutexFailure::RendezvousFailure & ) {      // if any members throw an exception
            switch(state) {
                case VendingMachine::State::free:             // When giving free drinks
                    printer->print( Printer::Kind::Vending, id, 'A' );
                    stock[currFlavour]--;                     // Reduce stock
                    break;
                case VendingMachine::State::funds:            // When waiting for funds
                    break;
                case VendingMachine::State::stocks:           // When out of stock
                    _Accept( inventory ) {                    // Accept request for inventory
                        printer->print(Printer::Kind::Vending, id, 'r' );
                        _Accept( restocked ) {                // Accept request for restock
                            printer->print(Printer::Kind::Vending, id, 'R');
                        } // _Accept

                    } or _Accept( ~VendingMachine ) {         // Accept destructor
                        break LOOP;
                    } // _Accept
                    break;
                default:
                    break;
            } // switch
        } // try
    } // for

} // VendingMachine::main


// ================== Public Member(s) ==================== //


void VendingMachine::buy( BottlingPlant::Flavours flavour, WATCard * card ) {
    if (stock[flavour] == 0) {                                  // If we are out of a flavour
        state = VendingMachine::State::stocks;
        _Throw VendingMachine::Stock{};                         // Throw stock exception
    } // if

    if (card->getBalance() < sodaCost) {                        // If we dont have enough money
        state = VendingMachine::State::funds;
        _Throw VendingMachine::Funds{};                         // Throw funds exception
    } // if

    // At this point we have enough funds, and theres enough stock of flavour

    VMCard = card;                                              // Store card for later
    currFlavour = flavour;                                      // Store flavour choice
    if (prng() % 4 == 0) {                                      // 1 in 4 chance for it to be free
        state = VendingMachine::State::free;
        _Throw VendingMachine::Free{};                          // Give soda for free
    } else {
        wait.wait();                                            // Wait for machine and card to be updated
    } // if
} // VendingMachine::buy

unsigned int * VendingMachine::inventory() {
    return stock;
} // VendingMachine::inventory

void VendingMachine::restocked() {
} // VendingMachine::restocked

_Nomutex unsigned int VendingMachine::cost() const {
    return sodaCost;
} // VendingMachine::cost

_Nomutex unsigned int VendingMachine::getId() const {
    return id;
} // VendingMachine::getId


// ================== Constructor / Destructor ==================== //


VendingMachine::VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost ):
printer(&prt), nameServer( &nameServer ), id(id), sodaCost(sodaCost) {
    printer->print( Printer::Kind::Vending, id, 'S', sodaCost );

} // VendingMachine::VendingMachine

VendingMachine::~VendingMachine() {
    printer->print( Printer::Kind::Vending, id, 'F' );

} // VendingMachine::~VendingMachine