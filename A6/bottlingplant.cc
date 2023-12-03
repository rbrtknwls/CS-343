#include "bottlingplant.h"
#include <uPRNG.h>

#ifndef

BottlingPlant::BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
                             unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
                             unsigned int timeBetweenShipments ) : printer(prt), nameServer(nameServer), numVendingMachines(numVendingMachines),
                             maxShippedperFlavour(maxShippedPerFlavour), maxStockperFlavour(maxStockPerFlavour), timeBetweenShipments(timeBetweenShipments), 
                             truck(printer, nameServer, *this, numVendingMachines, maxStockPerFlavour) {
} // BottlingPlant::BottlingPlant   

void BottlingPlant::main() {
    printer.print(Printer::Kind::BottlingPlant, 'S');
    try {
        for (;;) {
            yield(timeBetweenShipments); // wait for prod
            unsigned int totalBottles = 0;
            for (unsigned int i = 0; i < 4; i++) {
                int bottles = prng(maxShippedperFlavour);
                prod[i] = bottles;
                totalBottles += bottles;
            } // for

            printer.print(Printer::Kind::BottlingPlant, 'G', totalBottles);

            _Accept(~BottlingPlant) {
                shutdown = true
                _Accept(getShipment);
            } or _Accept(getShipment) {
                printer.print(Printer::Kind::BottlingPlant, 'P');
            } // _Accept
        } // for
    } catch (uMutexFailure::RendezvousFailure &) {
        printer.print(Printer::Kind::BottlingPlant, 'F');
    } // try
} // BottlingPlant::main


void BottlingPlant::getShipment( unsigned int cargo[] ) {
    if (shutdown) {
        throw BottlingPlant::Shutdown{};
    } // if
    for (unsigned int i = 0; i < 4; i++) {
        cargo[i] = prod[i];
    } // for
} // BottlingPlant::getShipment

BottlingPlant::~BottlingPlant() {
} // BottlingPlant::~BottlingPlant