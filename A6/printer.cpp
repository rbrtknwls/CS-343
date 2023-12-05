#include "printer.h"
#include <string>
#include <iostream>

using namespace std;

// ================== Private Method(s) ==================== //

// This method is used to convert the public enum into the local enum which we use when flushing the buffer
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
    } // switch
} // Printer::kindToID

// Update cout with the updated states for all terms (once we were going to rewrite them)
void Printer::flushBuffer () {

    for ( unsigned int id = 0; id < totalNumberOfActors; id++ ) {
        if ( hasBeenWrittenTo[id] ) {                                      // If actor has relevant update

            string toPrint = "";                                           // Store size of print
            switch ( printBuffer[id].numTerms ) {                          // Different syntax for size of update
                case ( 3 ):
                    toPrint = "," + to_string(printBuffer[id].value2);
                case ( 2 ):
                    toPrint = to_string(printBuffer[id].value1) + toPrint;
                default:
                    toPrint = printBuffer[id].mainState + toPrint;
            } // switch

            cout << toPrint;                                               // Print update
            cout << string(8 - toPrint.length(), ' ');                     // Print spacing for uniform placement

        } else {
            cout << "        ";
        } // if
    } // for
    cout << endl;

    // Update the state of all actors to reflect that they are now empty
    for ( unsigned int i = 0; i < totalNumberOfActors; i++ ) { hasBeenWrittenTo[i] = false; }
}

// ================== Constructor / Destructor ==================== //

Printer::Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers ) :
        numStudents(numStudents), numVendingMachines(numVendingMachines), numCouriers(numCouriers) {

    // Store total number of actors to consider
    totalNumberOfActors = numStudents + numVendingMachines + numCouriers + NUMBEROFSTATICACTORS;
    hasBeenWrittenTo = new bool[totalNumberOfActors];                 // Create bool for each actor
    printBuffer = new PrinterState[totalNumberOfActors];              // Create an data struct for each actor

    // This is for printing the headings at the top of the program
    for ( unsigned int id = 0; id < totalNumberOfActors; id++ ) {     // loop through each actor

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
                } // if
        } // switch

        cout << toPrint;
        cout << string( 8 - toPrint.length(), ' ' );
    } // for
    cout << endl;

    for ( unsigned int i = 0; i < totalNumberOfActors; i++ ) {
        cout << "*******";
        if ( i != totalNumberOfActors-1 ) { cout << " "; }
    } //for

    cout << endl;
}

Printer::~Printer() {
    Printer::flushBuffer();                                        // Flush the buffer at the end

    cout << "***********************" << endl;

    delete printBuffer;
    delete hasBeenWrittenTo;
} // Printer::~Printer

// ================== Public Member(s) ==================== //

// Generic print for only the state
void Printer::print( Kind kind, char state ) {
    int id = kindToID( kind );
    if ( hasBeenWrittenTo[id] ) { flushBuffer(); }

    printBuffer[id].mainState = state;
    printBuffer[id].numTerms = 1;

    hasBeenWrittenTo[id] = true;
} // Printer::print

// Generic print for only the state and a single value
void Printer::print( Kind kind, char state, unsigned int value1 ) {
    int id = kindToID( kind );
    if ( hasBeenWrittenTo[id] ) { flushBuffer(); }

    printBuffer[id].mainState = state;
    printBuffer[id].value1 = value1;
    printBuffer[id].numTerms = 2;

    hasBeenWrittenTo[id] = true;
} // Printer::print

// Generic print for only the state and two values
void Printer::print( Kind kind, char state, unsigned int value1, unsigned int value2 ) {
    int id = kindToID( kind );
    if ( hasBeenWrittenTo[id] ) { flushBuffer(); }

    printBuffer[id].mainState = state;
    printBuffer[id].value1 = value1;
    printBuffer[id].value2 = value2;
    printBuffer[id].numTerms = 3;

    hasBeenWrittenTo[id] = true;
} // Printer::print

// Specific for lid print, only for the state
void Printer::print( Kind kind, unsigned int lid, char state ) {
    int id = kindToID( kind ) + lid;
    if ( hasBeenWrittenTo[id] ) { flushBuffer(); }

    printBuffer[id].mainState = state;
    printBuffer[id].numTerms = 1;

    hasBeenWrittenTo[id] = true;
} // Printer::print

// Specific for lid print, only for the state and a value
void Printer::print( Kind kind, unsigned int lid, char state, unsigned int value1 ) {
    int id = kindToID( kind ) + lid;
    if ( hasBeenWrittenTo[id] ) { flushBuffer(); }

    printBuffer[id].mainState = state;
    printBuffer[id].value1 = value1;
    printBuffer[id].numTerms = 2;

    hasBeenWrittenTo[id] = true;
} // Printer::print

// Specific for lid print, only for the state and two values
void Printer::print( Kind kind, unsigned int lid, char state, unsigned int value1, unsigned int value2 ) {
    int id = kindToID( kind ) + lid;
    if ( hasBeenWrittenTo[id] ) { flushBuffer(); }

    printBuffer[id].mainState = state;
    printBuffer[id].value1 = value1;
    printBuffer[id].value2 = value2;
    printBuffer[id].numTerms = 3;

    hasBeenWrittenTo[id] = true;
} // Printer::print