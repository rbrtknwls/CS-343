#include "watCard.h"


// ================== Public Member(s) ==================== //


// Mutex member for depositing money into a watcard
void WATCard::deposit( unsigned int amount ) { balance += amount; }

// Mutex member for withdrawing money from a watcard
void WATCard::withdraw( unsigned int amount ) { balance -= amount; }

// Mutex member for getting the balance of a watcard
unsigned int WATCard::getBalance() { return balance; }

// ================== Constructor / Destructor ==================== //

WATCard::WATCard() : balance(0) { }