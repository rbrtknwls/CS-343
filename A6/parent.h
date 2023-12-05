#ifndef CS_343_PARENT_H
#define CS_343_PARENT_H

#include <uPRNG.h>

#include "printer.h"
#include "bank.h"

_Task Parent {
    Printer *printer;
    Bank *bank;
    unsigned int numStudents, parentalDelay;

    void main();
  public:
    Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay );
    ~Parent();
};


#endif //CS_343_PARENT_H
