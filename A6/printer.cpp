#include "printer.h"
#include <string>
#include <iostream>

using namespace std;

// ================== Private Method(s) ==================== //

void Printer::flushBuffer () {
    for (unsigned int id = 0; id < totalNumberOfActors; id++ ) {
        if ( hasBeenWrittenTo[id] ) {

            string toPrint = "";
            switch ( printBuffer[id].numTerms ) {
                case ( 3 ):
                    toPrint = "," + to_string(printBuffer[id].value2);
                case ( 2 ):
                    toPrint = to_string(printBuffer[id].value1) + toPrint;
                default:
                    toPrint = printBuffer[id].mainState + toPrint;
            }

            cout << toPrint;
            cout << string(8 - toPrint.length(), ' ');

        }
    }

    for ( unsigned int i = 0; i < totalNumberOfActors; i++ ) { hasBeenWrittenTo[i] = false; }
}
// ================== Constructor / Destructor ==================== //

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) :
        numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers) {

    totalNumberOfActors = numStudents + numVendingMachines + numCouriers + NUMBEROFSTATICACTORS;
    hasBeenWrittenTo = new bool[totalNumberOfActors];
    printBuffer = new PrinterState[totalNumberOfActors];

    for ( unsigned int id = 0; id < totalNumberOfActors; id++ ) {

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
                if ( id < NUMBEROFSTATICACTORS + numStudents ) {
                    toPrint = "Stud" + std::to_string(id - NUMBEROFSTATICACTORS - 1);
                    break;
                }
                else if (id < NUMBEROFSTATICACTORS + numStudents + numVendingMachines) {
                    toPrint = "Mach" + std::to_string(id - NUMBEROFSTATICACTORS - numStudents - 1);
                    break;
                } else {
                    toPrint = "Cour" + std::to_string(id - NUMBEROFSTATICACTORS - numStudents - numVendingMachines);
                    break;
                }
        }

        cout << toPrint;
        cout << string(8 - toPrint.length(), ' ');
    }
    cout << endl;

    for ( unsigned int i = 0; i < totalNumberOfActors; i++ ) {
        cout << "*******";
        if ( i != totalNumberOfActors-1 ) { cout << " "; }
    }

    cout << endl;
}

Printer::~Printer() {
    //Printer::flushBuffer();

    cout << "***********************" << endl;

    delete printBuffer;
    delete hasBeenWrittenTo;
}

