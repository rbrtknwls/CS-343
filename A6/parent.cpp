#include "parent.h"

// ================== Private Member(s) ==================== //

void Parent::main() {

    for ( ;; ) {

        _Accept( ~Parent ) { break; }
        _Else {
            yield( parentalDelay );
            int idOfStudent = prng( numStudents );
            int moneyToDeposit = prng( 3 ) + 1;
            bank->deposit( idOfStudent, moneyToDeposit );
            printer->print( Printer::Parent, 'D', idOfStudent, moneyToDeposit );
        }

    }

}

// ================== Constructor / Destructor ==================== //

Parent::Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay ) :
    printer( &prt ), bank( &bank ), numStudents( numStudents ), parentalDelay( parentalDelay ) {

    printer->print( Printer::Parent, 'S' );

}

Parent::~Parent() { printer->print( Printer::Parent, 'F' ); }
