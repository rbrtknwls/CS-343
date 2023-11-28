#ifndef CS_343_PARENT_H
#define CS_343_PARENT_H

#include "printer.h"

_Monitor Bank;

_Task Parent {
    void main();
  public:
    Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay );
};


#endif //CS_343_PARENT_H
