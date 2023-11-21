#include "q3tallyVotes.h"
#include "q3voter.h"
#include "q3printer.h"

/*
 * Semaphore implementation of tally voters, this contains both the vote method and the done method. All the other
 *  methods that are needed for tally votes are implemented in the generic tallyVotes.cpp
 */

TallyVotes::Tour TallyVotes::vote( unsigned id, Ballot ballot ) {

    printer->print( id, Voter::Vote, ballot );

    votes[0] += ballot.picture;
    votes[1] += ballot.statue;
    votes[2] += ballot.giftshop;
    
    return currentTour;

}

void TallyVotes::done( unsigned id ) {
    printer->print(id, Voter::Terminated);
    voters--;

    if ( voters < maxGroupSize ) {

    }
}