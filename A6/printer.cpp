#include "printer.h"
#include <string>
#include <iostream>

using namespace std;

// ================== Public Methods ==================== //

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) :
        numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers) {

    hasBeenWrittenTo = new bool[numStudents + numVendingMachines + numCouriers + NUMBEROFOTHERACTORS];
    printBuffer = new PrinterState[numStudents + numVendingMachines + numCouriers + NUMBEROFOTHERACTORS];


    for ( unsigned int id = 0; id < NUMBEROFOTHERACTORS; id++ ) {
        hasBeenWrittenTo[i] = false;

        string toPrint;
        switch ( id ) {
            case PARENTID:
                toPrint = "Parent";
                break;
            case GROPOFFID:
                toPrint = "Gropoff";
                break;
            case WATOFFID:
                toPrint = "WATOff";
                break;
            case NAMESID:
                toPrint = "Truck";
                break;
            case PLANTID:
                toPrint = "Plant";
                break;
        }
        nonSpaceValues += toPrint.length();

        std << toPrint;
        std << string(8 - nonSpaceValues, ' ');
    }
    cout << endl;

    for ( unsigned int i = 0; i < numStudents + numVendingMachines + numCouriers + NUMBEROFOTHERACTORS; i++ ) {
        cout << "*******";
        if ( i != numStudents + numVendingMachines + numCouriers + NUMBEROFOTHERACTORS-1 ) { cout << " "; }
    }

    cout << endl;
#endif
}