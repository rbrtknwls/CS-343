#ifndef CS_343_Q3PRINTER_H
#define CS_343_Q3PRINTER_H

#include "q3voter.h"
#include "q3tallyVotes.h"

#if defined( MC ) || defined( SEM )
_Monitor Printer {
#elif defined( BAR )
_Cormonitor Printer {
#endif

  public:
    Printer( unsigned int voters );
    void print( unsigned int id, Voter::States state );
    void print( unsigned int id, Voter::States state, TallyVotes::Tour tour );
    void print( unsigned int id, Voter::States state, TallyVotes::Ballot vote );
    void print( unsigned int id, Voter::States state, unsigned int numBlocked );
    void print( unsigned int id, Voter::States state, unsigned int numBlocked, unsigned int group );
};


#endif //CS_343_Q3PRINTER_H
