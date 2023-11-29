#include "parent.h"

// ================== Private Member(s) ==================== //

void Parent::main() {

    for ( ;; ) {

        _Accept( ~Parent ) { break; }
        _Else {

        }

    }

}

// ================== Constructor / Destructor ==================== //

Parent::Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay ) :
    Printer(prt), Bank(bank), numStudents(numStudents), parentalDelay(parentalDelay) {}


