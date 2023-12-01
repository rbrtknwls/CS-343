#include <iostream>
#include <vector>
#include <uPRNG.h>

#include "config.h"
#include "printer.h"
#include "bank.h"
#include "parent.h"
#include "watCardOffice.h"
#include "watCard.h"
using namespace std;

PRNG mainPRNG;

int main( int argc, char * argv[] ) {

    char * configFile = (char*) "soda.config";
    int processors = 1;

    struct cmd_error { };
    try {
        switch ( argc ) {
            case 4:
                if ( *argv[3] != 'd' ) { processors = stoi(argv[3]); }
            case 3:
                if ( *argv[2] != 'd' ) {
                    int seed = stoi(argv[2]);
                  if (seed <= 0) { throw cmd_error(); }
                    mainPRNG.set_seed(seed);
                }
            case 2:
                if ( *argv[1] != 'd' ) { configFile = argv[1]; }
            default:
                if ( processors <= 0 ) { throw cmd_error(); }
                break;
        }

    } catch (...) {
        cerr << "Usage: " << argv[0]
             << " [ config-file | ’d’ [ seed (> 0) | ’d’ [ processors (> 0) | ’d’ ] ] ]"  << endl;
        exit(EXIT_FAILURE);
    }
    uProcessor p[processors - 1] __attribute__(( unused ));

    ConfigParms parameters;
    processConfigFile( configFile, parameters );

    // Setup
    Printer printer = Printer( parameters.numStudents, parameters.numVendingMachines, parameters.numCouriers );

    Bank bank = Bank( parameters.numStudents );
    Parent parent = Parent( printer, bank, parameters.numStudents, parameters.parentalDelay );

    WATCardOffice watCardOffice = WATCardOffice( printer, bank, parameters.numCouriers );

    WATCard::FWATCard watcard = watCardOffice.create(0, 5);
    delete watcard;
}
