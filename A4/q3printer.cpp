#include "q3printer.h"
#include <iostream>

void flushBuffer ( int voters, bool* hasBeenWrittenTo, PrinterState *buffer ) {

}

Printer::Printer( unsigned int voters ) : voters(voters) {
    hasBeenWrittenTo = new bool[voters];
    printBuffer = new PrinterState[voters];


    for ( unsigned int i = 0; i < voters; i++ ) {
        std::cout <<
        hasBeenWrittenTo[i] = false;
    }
}

Printer::~Printer() {
    delete printBuffer;
    delete hasBeenWrittenTo;
}

