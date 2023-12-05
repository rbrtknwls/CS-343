#include "bank.h"

// ================== Public Member(s) ==================== //

// Method used to deposit money into the bank account of the student
void Bank::deposit( unsigned int id, unsigned int amount ) { studentBalances[id] += amount; }

// Method used to withdraw money from an account (may wait on more deposits)
void Bank::withdraw( unsigned int id, unsigned int amount ) {
    while ( amount > studentBalances[id] ) { _Accept( deposit ); }
    studentBalances[id] -= amount;
}

// ================== Constructor / Destructor ==================== //

Bank::Bank( unsigned int numStudents ) {
    studentBalances = new unsigned int[numStudents];

    for ( unsigned int studentID = 0; studentID < numStudents; studentID++ ) {
        studentBalances[studentID] = 0;
    }

}

Bank::~Bank() { delete studentBalances; }