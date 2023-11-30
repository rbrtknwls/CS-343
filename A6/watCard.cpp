#include "watCard.h"

// ================== Public Member(s) ==================== //

void WATCard::deposit( unsigned int amount ) { balance -= amount; }
void WATCard::withdraw( unsigned int amount ) { balance += amount; }
unsigned int WATCard::getBalance() { return balance; }

// ================== Constructor / Destructor ==================== //

WATCard::WATCard() { balance = 0; }