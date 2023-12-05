#include <iostream>
#include <vector>
#include <uPRNG.h>

#include "config.h"
#include "printer.h"
#include "bank.h"
#include "parent.h"
#include "watCardOffice.h"
#include "watCard.h"
#include "groupoff.h"
#include "student.h"
#include "bottlingplant.h"
#include "truck.h"
#include "vendingmachine.h"
#include "nameserver.h"

using namespace std;

PRNG mainPRNG;

int main( int argc, char * argv[] ) {

    char * configFile = (char*) "soda.config";
    int processors = 1;

    struct cmd_error { };
    try {
        switch ( argc ) {
            case 5:
                throw cmd_error();
            case 4:
                if ( *argv[3] != 'd' ) { processors = stoi(argv[3]); }
            case 3:
                if ( *argv[2] != 'd' ) {
                    int seed = stoi(argv[2]);
                  if (seed <= 0) { throw cmd_error(); }
                    set_seed(seed);
                }
            case 2:
                if ( *argv[1] != 'd' ) { configFile = argv[1]; }
            default:
                if ( processors <= 0 ) { throw cmd_error(); }
                break;
        }

    } catch (...) {
        cerr << "Usage: " << argv[0]
             << " [ config-file | 'd' (default file soda.config) [ seed (> 0) | 'd' (default random) ["
             << " processors (> 0) | 'd' (default 1) ] ] ]"  << endl;
        exit(EXIT_FAILURE);
    }
    uProcessor p[processors - 1] __attribute__(( unused ));

    ConfigParms parameters;
    processConfigFile( configFile, parameters );

    Printer printer = Printer( parameters.numStudents, parameters.numVendingMachines, parameters.numCouriers );

    Bank bank = Bank( parameters.numStudents );
    Parent parent = Parent( printer, bank, parameters.numStudents, parameters.parentalDelay );

    WATCardOffice watCardOffice = WATCardOffice( printer, bank, parameters.numCouriers );
    Groupoff groupoffer = Groupoff( printer, parameters.numStudents, parameters.sodaCost, parameters.groupoffDelay );

    NameServer nameServer = NameServer( printer, parameters.numVendingMachines, parameters.numStudents );
    VendingMachine * vendingMachines[parameters.numVendingMachines];

    for ( unsigned int vendingID = 0; vendingID < parameters.numVendingMachines; vendingID++ ) {
        vendingMachines[vendingID] = new VendingMachine( printer, nameServer, vendingID, parameters.sodaCost );
    }


    

    BottlingPlant * bottlingPlant = new BottlingPlant( printer, nameServer, parameters.numVendingMachines,
                                                    parameters.maxShippedPerFlavour, parameters.maxStockPerFlavour,
                                                    parameters.timeBetweenShipments );

    Student * students[parameters.numStudents];

    for (unsigned int studentID = 0; studentID < parameters.numStudents; studentID++) {
        students[studentID] = new Student(printer, nameServer, watCardOffice, groupoffer, studentID, parameters.maxPurchases);
    }

    

    for ( unsigned int studentID = 0; studentID < parameters.numStudents; studentID++ ) {
        delete students[studentID];
    }

    delete bottlingPlant;

    for ( unsigned int vendingID = 0; vendingID < parameters.numVendingMachines; vendingID++ ) {
        delete vendingMachines[vendingID];
    }
}
