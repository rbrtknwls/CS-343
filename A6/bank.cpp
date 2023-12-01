#include "bank.h"

// ================== Public Member(s) ==================== //

void Bank::deposit( unsigned int id, unsigned int amount ) { studentBalances[id] += amount; }

void Bank::withdraw( unsigned int id, unsigned int amount ) {
    while ( amount > studentBalances[id] ) { _Accept( deposit ); }
    studentBalances[id] -= amount;
}

// ================== Constructor / Destructor ==================== //

Bank::Bank( unsigned int numStudents ) { studentBalances = new unsigned int[numStudents]; }

Bank::~Bank() { delete studentBalances; }