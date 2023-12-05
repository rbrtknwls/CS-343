#include "truck.h"
#include <uPRNG.h>
#include <algorithm>
#include "bottlingplant.h"
#include "vendingmachine.h"

using namespace std;


// ================== Private Method(s) ==================== //


void Truck::main() {

    VendingMachine **machines = nameServer.getMachineList();
    unsigned int currMachine = 0;
    unsigned int totalSodas = 0;
    unsigned int loop_count = 0;

    VendingMachine *machine;
    unsigned int *stock;
    unsigned int totalLacking = 0;

    printer.print(Printer::Kind::Truck, 'F');
    printer.print(Printer::Kind::Truck, 'F');

    for ( ;; ) {

        yield( prng( 10 ) );

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

        for ( loop_count = numVendingMachines ; loop_count > 0; loop_count--) {
            if ( totalSodas == 0 ) { break; }
            if ( currMachine == numVendingMachines ) { currMachine = 0; }

            machine = machines[currMachine];
            stock = machine->inventory();
            totalLacking = 0;

            printer.print(Printer::Kind::Truck, 'd', currMachine, totalSodas);
            calcUsed(stock, sodas, totalLacking, totalSodas);

            if ( totalLacking > 0 ) { printer.print(Printer::Kind::Truck, 'U', currMachine, totalLacking); }

            printer.print(Printer::Kind::Truck, 'D', currMachine, totalSodas);
            machine->restocked();

            if (prng()%100 == 0) { // if flat tire
                printer.print(Printer::Kind::Truck, 'W');
                yield(10);
            } // if

            currMachine++;
        } // for

    } // for

} // Truck::main

void Truck::calcUsed(unsigned int* stock, unsigned int* sodas, unsigned int& totalLacking, unsigned int& totalSodas) {
    for (unsigned int i = 0; i < 4; i++) {
        unsigned int sodas_got = min(sodas[i], maxStockPerFlavour - stock[i]);
        totalSodas -= sodas_got;
        sodas[i] -= sodas_got;
        stock[i] += sodas_got;
        totalLacking += maxStockPerFlavour - stock[i];
    } // for
} // Truck::calcUsed


// ================== Constructor / Destructor ==================== //


Truck::Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
              unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) : printer(prt), nameServer(nameServer),
numVendingMachines(numVendingMachines), maxStockPerFlavour(maxStockPerFlavour), bottlingPlant(plant) {
    printer.print(Printer::Kind::Truck, 'S');
    printer.print(Printer::Kind::Truck, 'S');
    printer.print(Printer::Kind::Truck, 'S');
} // Truck::Truck

Truck::~Truck() {
    printer.print(Printer::Kind::Truck, 'F');
} // Truck::~Truck