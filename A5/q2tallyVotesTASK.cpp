#include "q2tallyVotes.h"
#include "q2voter.h"
#include "q2printer.h"

#include <stdlib.h>

void TallyVotes::main() {
    for ( ;; ) {
        printer->print( currendId, Voter::Vote, currentBallot );
    }
}

TallyVotes::Tour TallyVotes::vote( unsigned id, Ballot ballot ) {
    currentBallot = ballot;
    currentId = id;

    //bench.wait();

    return currentTour;

}

void TallyVotes::done( unsigned int id ) {
    voters--;
}