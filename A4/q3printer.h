#ifndef CS_343_Q3PRINTER_H
#define CS_343_Q3PRINTER_H

#include "q3tallyVotes.h"
#include "q3voter.h"

/*
struct PrinterState {
    Voter::States mainState,
    unsigned int val1,
    unsigned int val2,
    unsigned int val3
};*/

_Monitor Printer {
    unsigned int voters;
    //PrinterState printBuffer*;
    bool *hasBeenWrittenTo;

  public:
    Printer( unsigned int voters );
    void print( unsigned int id, Voter::States state );
    void print( unsigned int id, Voter::States state, TallyVotes::Tour tour );
    void print( unsigned int id, Voter::States state, TallyVotes::Ballot vote );
    void print( unsigned int id, Voter::States state, unsigned int numBlocked );
    void print( unsigned int id, Voter::States state, unsigned int numBlocked, unsigned int group );

};

#endif //CS_343_Q3PRINTER_H
