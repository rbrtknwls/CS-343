#include "vendingmachine.h"
#include "printer.h"
#include "nameserver.h"
#include "watCard.h"

void VendingMachine::main() {

    //nameServer.VMregister( this );
    
    /*
    LOOP: for( ;; ) {
        printer.print(Printer::Kind::Vending, id, 'L', sodaCost);
        try {
            _Accept( ~VendingMachine ) {
                printer.print(Printer::Kind::Vending, id, 'L', sodaCost);
                printer.print(Printer::Kind::Vending, id, 'L', sodaCost);
                printer.print(Printer::Kind::Vending, id, 'L', sodaCost);
                break;

            } or _Accept( buy ) {
                VMCard->withdraw( sodaCost );
                stock[currFlavour]--;
                printer.print( Printer::Kind::Vending, id, 'B', currFlavour, stock[currFlavour] );
                wait.signalBlock();
            } or _Accept( inventory ) {
                printer.print(Printer::Kind::Vending, id, 'r');
                _Accept( restocked ) {
                    printer.print(Printer::Kind::Vending, id, 'R');
                } // _Accept
            } // _Accept
        } catch ( uMutexFailure::RendezvousFailure & ) {
            switch( state ) {
                case VendingMachine::State::free:
                    printer.print(Printer::Kind::Vending, id, 'A');

                    stock[currFlavour]--;
                    break;
                case VendingMachine::State::funds:
                    break;
                case VendingMachine::State::stocks:
                    _Accept( inventory ) {

                        printer.print(Printer::Kind::Vending, id, 'r');
                        _Accept( restocked ) {
                            printer.print(Printer::Kind::Vending, id, 'R');
                        } // _Accept

                    } or _Accept(~VendingMachine) {
                        break LOOP;
                    } // _Accept
                    break;
                default:
                    break;
            } // switch
        } // try
    } // for
    */
} // VendingMachine::main



void VendingMachine::buy( BottlingPlant::Flavours flavour, WATCard & card ) {
    if (stock[flavour] == 0) {
        state = VendingMachine::State::stocks;
        _Throw VendingMachine::Stock{};
    } // if

    if (card.getBalance() < sodaCost) {
        state = VendingMachine::State::funds;
        _Throw VendingMachine::Funds{};
    } // if

    VMCard = &card;
    currFlavour = flavour;
    if (prng() % 4 == 0) {
        state = VendingMachine::State::free;
        _Throw VendingMachine::Free{};
    } else {
        wait.wait();
    } // if
} // VendingMachine::buy



unsigned int * VendingMachine::inventory() { return stock; } // VendingMachine::inventory

void VendingMachine::restocked() { } // VendingMachine::restocked

_Nomutex unsigned int VendingMachine::cost() const { return sodaCost; } // VendingMachine::cost

_Nomutex unsigned int VendingMachine::getId() const { return id; } // VendingMachine::getId

// ================== Constructor / Destructor ==================== //

VendingMachine::VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost ):
    printer( &prt ), nameServer( &nameServer ), id(id), sodaCost(sodaCost) {

    printer->print(Printer::Kind::Vending, id, 'S', sodaCost);
} // VendingMachine::VendingMachine

VendingMachine::~VendingMachine() {

    printer->print(Printer::Kind::Vending, id, 'F', sodaCost);
}