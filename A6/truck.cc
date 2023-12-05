#include "truck.h"
#include <uPRNG.h>
#include <algorithm>
#include "bottlingplant.h"
#include "vendingmachine.h"

using namespace std;


// ================== Private Method(s) ==================== //

/*
 * Main method for the truck task, will loop between the bottling plant and vending machine.
 * It will update each of these according depending on the amount of stock required.
 */
void Truck::main() {

    VendingMachine **machines = nameServer.getMachineList();
    unsigned int currMachine = 0;
    unsigned int totalSodas = 0;
    unsigned int loop_count = 0;

    VendingMachine *machine;
    unsigned int *stock;
    unsigned int totalLacking = 0;


    for ( ;; ) {                                                     // Loop until shutdown of plant

        yield( prng( 10 ) );                                         // Wait a set amount of time


        // Will try to get a shipment, or will receive that the plant shut down (exception) and will exit
        try {
            _Enable {
                bottlingPlant.getShipment(sodas);
            }
        } catch ( BottlingPlant::Shutdown & ) {
            break;
        } // try

        for (unsigned int i = 0; i < 4; i++) {
            totalSodas += sodas[i];
        } // for

        printer.print(Printer::Kind::Truck, 'P', totalSodas);

        // Loop through the number of vending machines
        for ( loop_count = numVendingMachines ; loop_count > 0; loop_count--) {
            if ( totalSodas == 0 ) { break; }                          // Break if out of sodas
            if ( currMachine == numVendingMachines ) { currMachine = 0; }

            machine = machines[currMachine];                           // Get the current machine
            stock = machine->inventory();                              // Get stock of current machine
            totalLacking = 0;

            printer.print(Printer::Kind::Truck, 'd', currMachine, totalSodas);
            calcUsed(stock, sodas, totalLacking, totalSodas);          // Calculate amount of stock used

            if ( totalLacking > 0 ) { printer.print(Printer::Kind::Truck, 'U', currMachine, totalLacking); }

            printer.print(Printer::Kind::Truck, 'D', currMachine, totalSodas);
            machine->restocked();                                      // Signal machine is restocked

            if (prng()%100 == 0) {                                     // If flat tire
                printer.print(Printer::Kind::Truck, 'W');
                yield(10);
            } // if

            currMachine++;                                            // update current machine
        } // for

    } // for

} // Truck::main

void Truck::calcUsed(unsigned int* stock, unsigned int* sodas, unsigned int& totalLacking, unsigned int& totalSodas) {
    for (unsigned int i = 0; i < 4; i++) {                        // Loop through each flavour
        unsigned int sodas_got = min(sodas[i], maxStockPerFlavour - stock[i]);
        totalSodas -= sodas_got;
        sodas[i] -= sodas_got;
        stock[i] += sodas_got;
        totalLacking += maxStockPerFlavour - stock[i];            // Store number of flavours needed
    } // for
} // Truck::calcUsed

// ================== Constructor / Destructor ==================== //


Truck::Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
              unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) : printer(prt), nameServer(nameServer),
numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour), bottlingPlant(plant) {
    printer.print(Printer::Kind::Truck, 'S');
} // Truck::Truck

Truck::~Truck() {
    printer.print(Printer::Kind::Truck, 'F');
} // Truck::~Truck