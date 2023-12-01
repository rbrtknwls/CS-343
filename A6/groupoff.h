#ifndef CS_343_GROUPOFF_H
#define CS_343_GROUPOFF_H

#include "groupoff.h"
#include "printer.h"

_Task Groupoff {
    Printer *printer;
    unsigned int numStudents;
    unsigned int sodaCost;
    unsigned int groupoffDelay;

    void main();

  public:
    Groupoff( Printer & prt, unsigned int numStudents, unsigned int sodaCost, unsigned int groupoffDelay );
    WATCard::FWATCard giftCard();
};


#endif //CS_343_GROUPOFF_H
