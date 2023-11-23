#include "q2tallyVotes.h"
#include "q2voter.h"
#include "q2printer.h"

#include <stdlib.h>

void TallyVotes::main() {
    for ( ;; ) {
        printer->print( 1, Voter::Vote, currentBallot );
    }
}

TallyVotes::Tour TallyVotes::vote( unsigned id, Ballot ballot ) {
    TallyVotes::currentBallot = ballot;
    TallyVotes::currentId = id;

    bench.wait();

    return currentTour;

}

void TallyVotes::done( unsigned int id ) {
    voters--;
}