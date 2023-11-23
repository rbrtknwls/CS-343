#include "q2tallyVotes.h"
#include "q2voter.h"
#include "q2printer.h"

#include <stdlib.h>

void TallyVotes::main() {
    for ( ;; ) {
        try {
            _Accept( TallyVotes::vote ) {
                bench.signalBlock();
            } or _Accept( TallyVotes::done ) {
                printer->print( currentId, Voter::Vote, currentBallot );
                bench.signalBlock();
            }
        } catch ( uMutexFailure::RendezvousFailure& ) {

        }
    }
}

TallyVotes::Tour TallyVotes::vote( unsigned id, Ballot ballot ) {
    currentBallot = ballot;
    currentId = id;

    bench.wait();

    return currentTour;

}

void TallyVotes::done( unsigned int id ) {
    currentId = id;
    voters--;
}