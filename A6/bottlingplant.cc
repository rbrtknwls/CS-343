#include "bottlingplant.h"
#include <uPRNG.h>


// ================== Private Method(s) ==================== //


void BottlingPlant::main() {

    for ( ;; ) {

        yield( timeBetweenShipments ); // wait for prod
        unsigned int totalBottles = 0;

        for (unsigned int i = 0; i < 4; i++) {
            int bottles = prng( maxShippedperFlavour );
            prod[i] = bottles;
            totalBottles += bottles;
        } // for

        printer.print(Printer::Kind::BottlingPlant, 'G', totalBottles);

        _Accept( ~BottlingPlant ) {
            _Resume Shutdown() _At *truck;
            break;

        } or _Accept( getShipment ) {

            printer.print(Printer::Kind::BottlingPlant, 'P');
        } // _Accept
    } // for

} // BottlingPlant::main


// ================== Public Member(s) ==================== //


void BottlingPlant::getShipment( unsigned int cargo[] ) {

    for (unsigned int i = 0; i < 4; i++) {
        cargo[i] = prod[i];
    } // for

} // BottlingPlant::getShipment


// ================== Constructor / Destructor ==================== //


BottlingPlant::BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour, unsigned int timeBetweenShipments ) :
    printer(prt), nameServer(nameServer), numVendingMachines(numVendingMachines),
    maxShippedperFlavour(maxShippedPerFlavour), maxStockperFlavour(maxStockPerFlavour),
    timeBetweenShipments(timeBetweenShipments) {

    printer.print(Printer::Kind::BottlingPlant, 'S');
    truck = new Truck( printer, nameServer, *this, numVendingMachines, maxStockPerFlavour );
} // BottlingPlant::BottlingPlant

BottlingPlant::~BottlingPlant() {
    delete truck;
    printer.print(Printer::Kind::BottlingPlant, 'F');
} // BottlingPlant::~BottlingPlant