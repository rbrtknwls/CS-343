#include "printer.h"
#include <string>
#include <iostream>

using namespace std;

// ================== Private Method(s) ==================== //

int Printer::kindToID ( Kind kind ) {
    switch ( kind ) {
        case Kind::Parent:
            return IDS::PARENT;
        case Kind::Groupoff:
            return IDS::GROUPOFF;
        case Kind::WATCardOffice:
            return IDS::WATOFF;
        case Kind::NameServer:
            return IDS::NAMES;
        case Kind::Truck:
            return IDS::TRUCK;
        case Kind::BottlingPlant:
            return IDS::PLANT;
        case Kind::Student:
            return NUMBEROFSTATICACTORS;
        case Kind::Vending:
            return NUMBEROFSTATICACTORS + numStudents;
        default:
            return NUMBEROFSTATICACTORS + numStudents + numVendingMachines;
    }
}

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

        } else {
            cout << "\t";
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
            case GROUPOFF:
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
                    toPrint = "Stud" + std::to_string(id - NUMBEROFSTATICACTORS);
                    break;
                } else if (id < NUMBEROFSTATICACTORS + numStudents + numVendingMachines) {
                    toPrint = "Mach" + std::to_string(id - NUMBEROFSTATICACTORS - numStudents);
                    break;
                } else {
                    toPrint = "Cour" + std::to_string(id - NUMBEROFSTATICACTORS - numStudents - numVendingMachines);
                    break;
                }
        }

        cout << toPrint;
        cout << string( 8 - toPrint.length(), ' ' );
    }
    cout << endl;

    for ( unsigned int i = 0; i < totalNumberOfActors; i++ ) {
        cout << "*******";
        if ( i != totalNumberOfActors-1 ) { cout << " "; }
    }

    cout << endl;
}

Printer::~Printer() {
    Printer::flushBuffer();

    cout << "***********************" << endl;

    delete printBuffer;
    delete hasBeenWrittenTo;
}

// ================== Public Member(s) ==================== //

void Printer::print( Kind kind, char state ) {
    int id = kindToID( kind );
    if ( hasBeenWrittenTo[id] ) { flushBuffer(); }

    printBuffer[id].mainState = state;
    printBuffer[id].numTerms = 1;

    hasBeenWrittenTo[id] = true;
}

void Printer::print( Kind kind, char state, unsigned int value1 ) {
    int id = kindToID( kind );
    if ( hasBeenWrittenTo[id] ) { flushBuffer(); }

    printBuffer[id].mainState = state;
    printBuffer[id].value1 = value1;
    printBuffer[id].numTerms = 2;

    hasBeenWrittenTo[id] = true;
}

void Printer::print( Kind kind, char state, unsigned int value1, unsigned int value2 ) {
    int id = kindToID( kind );
    if ( hasBeenWrittenTo[id] ) { flushBuffer(); }

    printBuffer[id].mainState = state;
    printBuffer[id].value1 = value1;
    printBuffer[id].value2 = value2;
    printBuffer[id].numTerms = 3;

    hasBeenWrittenTo[id] = true;
}

void Printer::print( Kind kind, unsigned int lid, char state ) {
    int id = kindToID( kind ) + lid;
    if ( hasBeenWrittenTo[id] ) { flushBuffer(); }

    printBuffer[id].mainState = state;
    printBuffer[id].numTerms = 1;

    hasBeenWrittenTo[id] = true;
}

void Printer::print( Kind kind, unsigned int lid, char state, unsigned int value1 ) {
    int id = kindToID( kind ) + lid;
    if ( hasBeenWrittenTo[id] ) { flushBuffer(); }

    printBuffer[id].mainState = state;
    printBuffer[id].value1 = value1;
    printBuffer[id].numTerms = 2;

    hasBeenWrittenTo[id] = true;
}

void Printer::print( Kind kind, unsigned int lid, char state, unsigned int value1, unsigned int value2 ) {
    int id = kindToID( kind ) + lid;
    if ( hasBeenWrittenTo[id] ) { flushBuffer(); }

    printBuffer[id].mainState = state;
    printBuffer[id].value1 = value1;
    printBuffer[id].value2 = value2;
    printBuffer[id].numTerms = 3;

    hasBeenWrittenTo[id] = true;
}