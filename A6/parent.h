#ifndef CS_343_PARENT_H
#define CS_343_PARENT_H

#include "printer.h"
#include "bank.h"

extern PRNG mainPRNG;

_Task Parent {
    Printer *printer;
    Bank *bank;
    unsigned int numStudents, parentalDelay;

    void main();
  public:
    Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay );
    ~Printer();
};


#endif //CS_343_PARENT_H
