#ifndef CS_343_GROUPOFF_H
#define CS_343_GROUPOFF_H

#include <uPRNG.h>

#include "groupoff.h"
#include "printer.h"
#include "watCard.h"

_Task Groupoff {
    Printer *printer;
    int numStudents;
    unsigned int sodaCost;
    unsigned int groupoffDelay;
    int currentStudent;

    WATCard::FWATCard* giftCards;

    void main();

  public:
    Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
    WATCard::FWATCard giftCard();
    ~Groupoff();
};


#endif //CS_343_GROUPOFF_H
