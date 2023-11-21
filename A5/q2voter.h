#ifndef CS_343_Q3VOTER_H
#define CS_343_Q3VOTER_H

#include <uPRNG.h>
#include "q2tallyVotes.h"
extern PRNG mainPRNG;

_Monitor Printer;

// Header class for the voter
_Task Voter {
    unsigned int id;
    unsigned int nvotes;
    TallyVotes *voteTallier;                            // Store reference to voteTallier
    Printer *printer;                                   // Store reference to printer

    TallyVotes::Ballot cast() __attribute__(( warn_unused_result )) {  // cast 3-way vote
        // O(1) random selection of 3 items without replacement using divide and conquer.
        static const unsigned int voting[3][2][2] = { { {2,1}, {1,2} }, { {0,2}, {2,0} }, { {0,1}, {1,0} } };
        unsigned int picture = mainPRNG( 3 ), statue = mainPRNG( 2 );
        return (TallyVotes::Ballot){ picture, voting[picture][statue][0], voting[picture][statue][1] };
    }
    void main();
  public:
    enum States : char { Start = 'S', Vote = 'V', Block = 'B', Unblock = 'U', Barging = 'b',
                         Done = 'D', Complete = 'C', Going = 'G', Failed = 'X', Terminated = 'T' };
    Voter( unsigned int id, unsigned int nvotes, TallyVotes & voteTallier, Printer & printer );
};


#endif //CS_343_Q3VOTER_H
