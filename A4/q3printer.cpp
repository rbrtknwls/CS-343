#include "q3printer.h"

Printer::Printer( unsigned int voters ) : voters(voters) {
    hasBeenWrittenTo = new bool[voters];
    printBuffer = new PrinterState[voters];


    for ( unsigned int i = 0; i < voters; i++ ) {
        hasBeenWrittenTo[i] = false;
    }
}

Printer::~Printer() {
    delete printerBuffer;
    delete hasBeenWrittento;
}

