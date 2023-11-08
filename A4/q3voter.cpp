#include <iostream>
#include <uPRNG.h>

#include "q3voter.h"
#include "q3printer.h"

Voter::Voter( unsigned int id, unsigned int nvotes, TallyVotes & voteTallier, Printer & printer ) :
    id(id), nvotes(nvotes), voteTallier(&voteTallier), printer(&printer) {}

void Voter::main() {
    yield ( prng( 19 ) );
    for ( unsigned int tourNum = 0; tourNum < nvotes; tourNum++ ) {
        printer->print(id, Start);
        yield( prng(4) );

        TallyVotes::Ballot ballot = cast();
        printer->print( id, Vote, ballot );
        TallyVotes::Tour groupResult = voteTallier->vote( id, ballot );

        yield( prng(4) );
        printer->print( id, Going, groupResult);
    }
    printer->print( id, Terminated);
}