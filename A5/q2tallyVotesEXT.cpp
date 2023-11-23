#include "q2tallyVotes.h"
#include "q2voter.h"
#include "q2printer.h"

/*
 * Implementation of TallyVotes done using internal scheduling.
 */

TallyVotes::Tour TallyVotes::vote( unsigned id, Ballot ballot ) {

    VOTER_ENTER( maxGroupSize );

    if ( voters < maxGroupSize ) { _Throw Failed(); }                     // Catch Quorum Failure

    printer->print( id, Voter::Vote, ballot );

    // Update votes with new voters preferences
    votes[0] += ballot.picture;
    votes[1] += ballot.statue;
    votes[2] += ballot.giftshop;

    currentNumberOfGroupMembers++;

    if (currentNumberOfGroupMembers == maxGroupSize) {                    // Only apply for the last member
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
                _Accept( TallyVotes::vote ) {                                // Wait until we get a vote

              break;                                                         // Break out of the loop

                } or _Accept( TallyVotes::done ) {                           // Check for done call

                    if ( voters < maxGroupSize ) {                           // Catch Quorum Failure

                        printer->print(id, Voter::Unblock, currentNumberOfGroupMembers - 1);

                        _Throw Failed();
                    } else {

                        printer->print(id, Voter::Done);                     // Blocked for "nothing", print Done

                    } // if

                } // _Accept ( Done )
            } // for
        } catch ( uMutexFailure::RendezvousFailure & ) {
            printer->print( id, Voter::Unblock, currentNumberOfGroupMembers - 1);

            _Throw Failed();
        } // catch

        printer->print( id, Voter::Unblock, currentNumberOfGroupMembers - 1);
    } // if
    currentNumberOfGroupMembers--;

    VOTER_LEAVE( maxGroupSize );

    return currentTour;

} // TallyVotes::vote

void TallyVotes::done() {
    voters--;
} // TallyVotes::done