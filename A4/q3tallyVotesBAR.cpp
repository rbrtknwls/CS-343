#include "q3tallyVotes.h"
#include "q3voter.h"
#include "q3printer.h"

/*
 * Semaphore implementation of tally voters, this contains both the vote method and the done method. All the other
 *  methods that are needed for tally votes are implemented in the generic tallyVotes.cpp
 */

TallyVotes::Tour TallyVotes::vote( unsigned id, Ballot ballot ) {

    if ( voters < maxGroupSize ) { _Throw Failed(); }   // Quorum failure

    printer->print( id, Voter::Vote, ballot );

    // Store the user's preferences as a sum
    votes[0] += ballot.picture;
    votes[1] += ballot.statue;
    votes[2] += ballot.giftshop;

    currentNumberOfGroupMembers++;
    if (currentNumberOfGroupMembers == maxGroupSize) { // Only apply for the last member
        currentTour.tourkind = determineWinner();
        currentTour.groupno = ++currentGroupNumber;

        // Reset the number of votes
        votes[0] = 0;
        votes[1] = 0;
        votes[2] = 0;

        block();                                        // This block will release all blockers

        printer->print( id, Voter::Complete, currentTour );

    } else {
        printer->print( id, Voter::Block, currentNumberOfGroupMembers );

        block();                                        // Block and wait
        if ( voters < maxGroupSize ) { _Throw Failed(); }

        printer->print( id, Voter::Unblock, currentNumberOfGroupMembers - 1);
    }
    currentNumberOfGroupMembers--;


    if ( voters < maxGroupSize ) { _Throw Failed(); }   // Quorum Failure
    return currentTour;

}

void TallyVotes::done( unsigned id ) {
    printer->print(id, Voter::Terminated);
    voters--;

    // This code will effectively flush the buffer and will release everyone. (the built in flush method gave an error)
    if ( voters < maxGroupSize ) {
        if ( waiters() != 0 ) { block(); }
    }
}