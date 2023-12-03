#ifndef CS_343_STUDENT_H
#define CS_343_STUDENT_H

#include "printer.h"
#include "watCardOffice.h"
#include "groupoff.h"

extern PRNG mainPRNG;

_Task Student {
    Printer *printer;
    WATCardOffice *watCardOffice;
    Groupoff *groupoff;

    unsigned int localId;
    unsigned int numberOfPurchases;
    unsigned int favouriteFlavour;

    void main();

  public:
    Student( Printer & prt, WATCardOffice & cardOffice, Groupoff & groupoff,
        unsigned int id, unsigned int maxPurchases );

};

#endif //CS_343_STUDENT_H
