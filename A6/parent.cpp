#include "parent.h"

// ================== Private Member(s) ==================== //

/*
 * This the main method of the parent task, it will deposit money into the bank account of a random student.
 */
void Parent::main() {

    for ( ;; ) {

        // Wait on the destructor of the parent
        _Accept( ~Parent ) { break; }
        _Else {
            yield( parentalDelay );                                // Wait [0, parentalDelay)
            int idOfStudent = prng( numStudents );                 // Get id of the student
            int moneyToDeposit = prng( 3 ) + 1;                    // Deposit [$1,$3] into student account
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
