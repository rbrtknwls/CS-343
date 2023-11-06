#ifndef CS_343_Q3PRINTER_H
#define CS_343_Q3PRINTER_H

#include "q3tallyVotes.h"
#include "q3voter.h"

_Monitor Printer {
    struct PrinterState {
        Voter::States mainState;
        TallyVotes::Tour tour;
        TallyVotes::Ballot vote;
        unsigned int numBlocked, group;
    };

    unsigned int voters;
    PrinterState *printBuffer;
    bool *hasBeenWrittenTo;

    void flushBuffer();
  public:
    Printer( unsigned int voters );
    void print( unsigned int id, Voter::States state );
    void print( unsigned int id, Voter::States state, TallyVotes::Tour tour );
    void print( unsigned int id, Voter::States state, TallyVotes::Ballot vote );
    void print( unsigned int id, Voter::States state, unsigned int numBlocked );
    void print( unsigned int id, Voter::States state, unsigned int numBlocked, unsigned int group );
    ~Printer();
};

#endif //CS_343_Q3PRINTER_H
