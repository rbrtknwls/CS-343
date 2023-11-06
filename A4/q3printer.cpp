#include "q3printer.h"

Printer::Printer( unsigned int voters ) : voters(voters) {
    hasBeenWrittenTo = new bool[voters];

    for ( int i = 0; i < voters; i++ ) {
        hasBeenWrittenTo[i] = false;
    }
}

