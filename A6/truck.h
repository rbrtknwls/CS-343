#ifndef TRUCK_H
#define TRUCK_H

#include "printer.h"
#include "nameserver.h"

_Task BottlingPlant;  // forward declaration


_Task Truck {
	void main();
    Printer & printer;
    NameServer & nameServer;
    unsigned int numVendingMachines;
    unsigned int maxStockPerFlavour;
    BottlingPlant & bottlingPlant;

    unsigned int sodas[4] = {0};
    void calcUsed(unsigned int* stock, unsigned int* sodas, unsigned int& totalLacking, unsigned int& totalSodas);
  public:
	Truck( Printer & prt, NameServer & nameServer, BottlingPlant & plant,
		   unsigned int numVendingMachines, unsigned int maxStockPerFlavour );
    ~Truck();
}; // Truck

#endif