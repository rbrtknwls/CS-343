#ifndef BOTTLINGPLANT_H
#define BOTTLINGPLANT_H

#include <uSemaphore.h>

#include "printer.h"
#include "truck.h"
#include "nameserver.h"

_Task BottlingPlant {
    void main();
    Printer & printer;
    NameServer & nameServer;
    unsigned int numVendingMachines;
    unsigned int maxShippedperFlavour;
    unsigned int maxStockperFlavour;
    unsigned int timeBetweenShipments;
    Truck truck;
    bool shutdown = false;
    unsigned int prod[4] = {0};


    public:
    enum Flavours {BlackCherry, CreamSoda, RootBeer, JazzLime, NUM_OF_FLAVOURS = 4};	// flavours of soda (YOU DEFINE)
	_Event Shutdown {};					// shutdown plant
	BottlingPlant( Printer & prt, NameServer & nameServer, unsigned int numVendingMachines,
				 unsigned int maxShippedPerFlavour, unsigned int maxStockPerFlavour,
				 unsigned int timeBetweenShipments );
	void getShipment( unsigned int cargo[] );
    ~BottlingPlant();
}; // BottlingPlant


#endif // BOTTLINGPLANT_H