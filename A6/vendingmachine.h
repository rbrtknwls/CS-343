#ifndef VENDINGMACHINE_H
#define VENDINGMACHINE_H

#include "bottlingplant.h"
#include "nameserver.h"
#include "printer.h"

class WATCard;

_Task VendingMachine {
	void main();
    Printer & printer;
    NameServer & nameServer;
    unsigned int id;
    unsigned int sodaCost;
    unsigned int stock[4] = {0};
    uCondition wait;
    WATCard* VMCard;
    BottlingPlant::Flavours currFlavour;
    enum State{stocks, free, funds};
    State state;
  public:
	_Event Free {};						// free, advertisement
	_Event Funds {};					// insufficient funds
	_Event Stock {};					// flavour out of stock
	VendingMachine( Printer & prt, NameServer & nameServer, unsigned int id, unsigned int sodaCost );
	void buy( BottlingPlant::Flavours flavour, WATCard & card );
	unsigned int * inventory() __attribute__(( warn_unused_result ));
	void restocked();
	_Nomutex unsigned int cost() const;
	_Nomutex unsigned int getId() const;
    ~VendingMachine();
}; // VendingMachine



#endif