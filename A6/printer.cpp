#include "printer.h"
#include <string>
#include <iostream>

using namespace std;

// ================== Public Methods ==================== //

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) :
        numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers) {


    hasBeenWrittenTo = new bool[numStudents + numVendingMachines + numCouriers + NUMBEROFSTATICACTORS];
    printBuffer = new PrinterState[numStudents + numVendingMachines + numCouriers + NUMBEROFSTATICACTORS];


    for ( unsigned int id = 0; id < numStudents + numVendingMachines + numCouriers + NUMBEROFSTATICACTORS; id++ ) {

        hasBeenWrittenTo[id] = false;
        string toPrint;
        switch ( id ) {
            case PARENT:
                toPrint = "Parent";
                break;
            case GROPOFF:
                toPrint = "Gropoff";
                break;
            case WATOFF:
                toPrint = "WATOff";
                break;
            case NAMES:
                toPrint = "Names";
                break;
            case TRUCK:
                toPrint = "Truck";
                break;
            case PLANT:
                toPrint = "Plant";
                break;
            default:
                if ( id <= NUMBEROFSTATICACTORS + numStudents ) {
                    toPrint = "Stud" + std::to_string(id - NUMBEROFSTATICACTORS);
                    break;
                }
                else if (id <= NUMBEROFSTATICACTORS + numStudents + numVendingMachines) {
                    toPrint = "Mach" + std::to_string(id - NUMBEROFSTATICACTORS - numStudents);
                    break;
                } else {
                    toPrint = " Cour" + std::to_string(id - NUMBEROFSTATICACTORS - numStudents - numVendingMachines);
                    break;
                }
        }

        cout << toPrint;
        cout << string(8 - toPrint.length(), ' ');
    }
    cout << endl;

    for ( unsigned int i = 0; i < numStudents + numVendingMachines + numCouriers + NUMBEROFSTATICACTORS; i++ ) {
        cout << "*******";
        if ( i != numStudents + numVendingMachines + numCouriers + NUMBEROFSTATICACTORS-1 ) { cout << " "; }
    }

    cout << endl;
}