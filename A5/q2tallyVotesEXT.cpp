#include "q2tallyVotes.h"
#include "q2voter.h"
#include "q2printer.h"

/*
 * Semaphore implementation of tally voters, this contains both the vote method and the done method. All the other
 *  methods that are needed for tally votes are implemented in the generic tallyVotes.cpp
 */

TallyVotes::Tour TallyVotes::vote( unsigned id, Ballot ballot ) {

    VOTER_ENTER( maxGroupSize );

    printer->print( id, Voter::Vote, ballot );

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

        printer->print( id, Voter::Complete, currentTour );

    } else {
        printer->print( id, Voter::Block, currentNumberOfGroupMembers );

        try {

            for ( ;; ) {
                _Accept( TallyVotes::vote ) {

              break;

                } or _Accept( TallyVotes::done ) {
                    if ( voters < maxGroupSize ) { _Throw Failed(); }
                }
            }

        } catch ( uMutexFailure::RendezvousFailure & ) {
            printer->print( id, Voter::Unblock, currentNumberOfGroupMembers - 1);

            _Throw Failed();
        }

        printer->print( id, Voter::Unblock, currentNumberOfGroupMembers - 1);
    }
    currentNumberOfGroupMembers--;


    if ( voters < maxGroupSize ) { _Throw Failed(); }   // Quorum Failure

    VOTER_LEAVE( maxGroupSize );

    return currentTour;

}

void TallyVotes::done() {
    voters--;
}