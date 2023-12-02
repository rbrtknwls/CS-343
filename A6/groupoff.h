#ifndef CS_343_GROUPOFF_H
#define CS_343_GROUPOFF_H

#include <uPRNG.h>

#include "groupoff.h"
#include "printer.h"

extern PRNG mainPRNG;

_Task Groupoff {
    Printer *printer;
    unsigned int numStudents;
    unsigned int sodaCost;
    unsigned int groupoffDelay;
    unsigned int currentStudent;

    void main();

    WATCard::FWATCard* giftCards;

  public:
    Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
    WATCard::FWATCard giftCard();
};


#endif //CS_343_GROUPOFF_H
