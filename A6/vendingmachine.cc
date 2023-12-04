#include "vendingmachine.h"
#include "printer.h"
#include "nameserver.h"
#include "watCard.h"
#include "bottlingplant.h"

VendingMachine::VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost,
                                unsigned int maxStockPerFlavour ) : printer(prt), nameServer(nameServer), id(id), sodaCost(sodaCost),
                                maxStockPerFlavour(maxStockPerFlavour) {
} // VendingMachine::VendingMachine

void VendingMachine::main() {
    printer.print(Printer::Kind::Vending, id, 'S', sodaCost);
    nameServer.VMregister(this);
    LOOP: for(;;) {
        try {
            _Accept(~VendingMachine) {
                break;
            } or _Accept(buy) {
                currCard->withdraw(sodaCost);
                stock[currFlavour]--;
                printer.print(Printer::Kind::Vending, id, 'B', currFlavour, stock[currFlavour]);
                wait.singalBlock();
            } or _Accept(inventory) {
                printer.print(Printer::Kind::Vending, id, 'r');
                _Accept(restocked) {
                    printer.print(Printer::Kind::Vending, id, 'R');
                } // _Accept
            } // _Accept
        } catch (uMutexFailure::RendezvousFailure &) {
            switch(state) {
                case VendingMachine::State::free:
                    printer.print(Printer::Kind::Vending, id, 'A');
                    stock[currFlavour]--;
                    break;
                case VendingMachine::State::funds:
                    break;
                case VendingMachine::State::stock:
                    _Accept(inventory) {
                        printer.print(Printer::Kind::Vending, id, 'r');
                        _Accept(restocked) {
                            printer.print(Printer::Kind::Vending, id, 'R');
                        } // _Accept
                    } or Accept(~VendingMachine) {
                        break LOOP;
                    } // _Accept
                    break;
                default:
                    break;
            } // switch
        } // try
    } // for

    printer.print(Printer::Kind::Vending, id, 'F');
} // VendingMachine::main


void VendingMachine::buy( Flavours flavour, WATCard & card ) {
    if (stock[flavour] == 0) {
        state = VendingMachine::State::stock;
        _Throw VendingMachine::Stock{};
    } // if
    if (card.getBalance() < sodaCost) {
        state = VendingMachine::State::funds;
        _Throw VendingMachine::Funds{};
    } // if

    currCard = &card;
    currFlavour = flavour;
    if (prng() % 4 == 0) {
        state = VendingMachine::State::free;
        _Throw VendingMachine::Free{};
    } else {
        wait.wait();
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