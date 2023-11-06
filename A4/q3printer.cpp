#include "q3printer.h"
#include <iostream>

void flushBuffer ( int voters, bool* hasBeenWrittenTo, PrinterState *buffer ) {

}

Printer::Printer( unsigned int voters ) : voters(voters) {
    hasBeenWrittenTo = new bool[voters];
    printBuffer = new PrinterState[voters];


    for ( unsigned int i = 0; i < voters; i++ ) {
        hasBeenWrittenTo[i] = false;
        cout << "V" << i;

        if ( i != voters-1 ) {
            if ( i < 10 ) { cout << "       "; }
            else { cout << "       "; }
        }
    }

    for ( unsigned int i = 0; i < voters; i++ ) {
        cout << "*******";
        if (i != voters-1 ) { cout << " "; }
    }
}

Printer::~Printer() {
    delete printBuffer;
    delete hasBeenWrittenTo;
}

