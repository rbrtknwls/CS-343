#include "truck.h"
#include <uPRNG.h>
#include <algorithm>
#include "bottlingplant.h"
#include "vendingMachine.h"

using namespace std;

Truck::Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
           unsigned int numVendingMachines, unsigned int maxStockPerFlavour ) : printer(prt), nameServer(nameServer), numVendingMachines(numVendingMachines),
           maxStockPerFlavour(maxStockPerFlavour), bottlingPlant(plant) {
} // Truck::Truck

void Truck::main() {
    printer.print(Printer::Kind::Truck, 'S');
    VendingMachine **machines = nameServer.getMachineList();
    unsigned int currMachine = 0;
    for (;;) {
        yield(prng(10));
        try {
            bottlingPlant.getShipment(sodas);
            unsigned int totalSodas = 0;
            for (unsigned int i = 0; i < 4; i++) {
                totalSodas += sodas[i];
            } // for
            printer.print(Printer::Kind::Truck, 'P', totalSodas);
            unsigned int loop_count = numVendingMachines
            for (; loop_count > 0; currMachine++) {
                if (totalSodas == 0) {
                    break;
                } // if
                if (currMachine == numVendingMachines) {
                    currMachine = 0;
                } // if
                VendingMachine *machine = machines[currMachine];
                unsigned int *stock = machine->inventory();
                unsigned int totalLacking = 0;
                printer.print(Printer::Kind::Truck, 'd', currMachine, totalSodas);
                calcUsed(stock, sodas, totalLacking, totalSodas);

                if (totalLacking > 0) {
                    printer.print(Printer::Kind::Truck, 'U', currMachine, totalLacking);
                } // if

                printer.print(Printer::Kind::Truck, 'D', currMachine, totalSodas);
                machine->restocked();

                if (prng()%100 == 0) { // if flat tire
                    printer.print(Printer::Kind::Truck, "W");
                    yield(10);
                } // if

                loop_count--;
            } // for
        } catch (BottlingPlant::Shutdown &) {
            break;
        } // try
    } // for
} // Truck::main

void Truck::calcUsed(unsinged int* stock, unsigned int* sodas, unsigned int& totalLacking, unsigned int& totalSodas) {
    for (unsigned int i = 0; i < 4; i++) {
        unsigned int sodas_got = min(sodas[i], maxStockPerFlavour - stock[i]);
        totalSodas -= sodas_got;
        sodas[i] -= sodas_got;
        stock[i] += sodas_got;
        totalLacking += maxStockPerFlavour - stock[i];
    } // for
} // Truck::calcUsed

Truck::~Truck() {
} // Truck::~Truck