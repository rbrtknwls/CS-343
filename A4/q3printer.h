#ifndef CS_343_Q3PRINTER_H
#define CS_343_Q3PRINTER_H

#include "q3tallyVotes.h"
#include "q3voter.h"


_Monitor Printer {
        public:
        Printer( unsigned int voters );
        void print( unsigned int id, Voter::States state );
        void print( unsigned int id, Voter::States state, TallyVotes::Tour tour );
        void print( unsigned int id, Voter::States state, TallyVotes::Ballot vote );
        void print( unsigned int id, Voter::States state, unsigned int numBlocked );
        void print( unsigned int id, Voter::States state, unsigned int numBlocked, unsigned int group );
};

#endif //CS_343_Q3PRINTER_H
