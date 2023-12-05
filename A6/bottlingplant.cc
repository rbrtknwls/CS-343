#include "bottlingplant.h"
#include <uPRNG.h>


// ================== Private Method(s) ==================== //

/*
 * Main method used by the bottling plant.
 * Will keep running until it gets a destructor, will destroy the truck and then exit
 */
void BottlingPlant::main() {

    for ( ;; ) {                                               // Loop until we get a destructor

        yield( timeBetweenShipments );                         // Wait for timeBetweenShipments
        unsigned int totalBottles = 0;

        for (unsigned int i = 0; i < 4; i++) {                 // Loop each flavour
            int bottles = prng( maxShippedperFlavour );
            prod[i] = bottles;
            totalBottles += bottles;
        } // for

        printer.print(Printer::Kind::BottlingPlant, 'G', totalBottles);

        _Accept( getShipment ) {                                // Accept get shipment

            printer.print(Printer::Kind::BottlingPlant, 'P');

        } or  _Accept( ~BottlingPlant ) {                       // Accept destructor

            _Accept( getShipment ) {                            // Allow truck to run (remove from calle)
                _Resume Shutdown() _At truck;                   // Throw exception and will stop truck
            }

            break;                                              // Exit

        } // _Accept
    } // for

} // BottlingPlant::main


// ================== Public Member(s) ==================== //

// Method used by truck to get a shipment (Error thrown by main!)
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
    timeBetweenShipments(timeBetweenShipments), truck( printer, nameServer, *this, numVendingMachines, maxStockPerFlavour ) {

    printer.print(Printer::Kind::BottlingPlant, 'S');
} // BottlingPlant::BottlingPlant

BottlingPlant::~BottlingPlant() {
    printer.print(Printer::Kind::BottlingPlant, 'F');
} // BottlingPlant::~BottlingPlant