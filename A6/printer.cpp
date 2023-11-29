#include "printer.h"
#include <string>
#include <iostream>

using namespace std;

// ================== Public Methods ==================== //

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) :
        numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers) {

    int numberOfStaticActors = Enum.GetNames(typeof(IDS)).Length;

    hasBeenWrittenTo = new bool[numStudents + numVendingMachines + numCouriers + numberOfStaticActors];
    printBuffer = new PrinterState[numStudents + numVendingMachines + numCouriers + numberOfStaticActors];


    for ( unsigned int id = 0; id < numberOfStaticActors; id++ ) {

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
                toPrint = "Truck";
                break;
            case PLANT:
                toPrint = "Plant";
                break;
        }

        std << toPrint;
        std << string(8 - toPrint.length(), ' ');
    }
    cout << endl;

    for ( unsigned int i = 0; i < numStudents + numVendingMachines + numCouriers + NUMBEROFOTHERACTORS; i++ ) {
        cout << "*******";
        if ( i != numStudents + numVendingMachines + numCouriers + NUMBEROFOTHERACTORS-1 ) { cout << " "; }
    }

    cout << endl;
}