#ifndef CS_343_PARENT_H
#define CS_343_PARENT_H

_Monitor Printer;

_Task Parent {
    void main();
  public:
    Parent( Printer & prt, Bank & bank, unsigned int numStudents, unsigned int parentalDelay );
};


#endif //CS_343_PARENT_H
