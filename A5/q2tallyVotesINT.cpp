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

    // Update votes with current voters preferences
    votes[0] += ballot.picture;
    votes[1] += ballot.statue;
    votes[2] += ballot.giftshop;

    currentNumberOfGroupMembers++;                                       // Update number of members in group

    if (currentNumberOfGroupMembers == maxGroupSize) {                   // Only applies for the last member
        currentTour.tourkind = determineWinner();
        currentTour.groupno = ++currentGroupNumber;

        // Reset the number of votes
        votes[0] = 0;
        votes[1] = 0;
        votes[2] = 0;


        printer->print( id, Voter::Complete, currentTour );

    } else {
        printer->print( id, Voter::Block, currentNumberOfGroupMembers );

        votingGroup.wait();                                              // wait for group to assemble

        printer->print( id, Voter::Unblock, currentNumberOfGroupMembers - 1);
    } // if
    currentNumberOfGroupMembers--;                                       // update number of group members

    votingGroup.signal();                                                // wake up any waiters

    if ( voters < maxGroupSize ) { _Throw Failed(); }                    // Quorum Failure

    VOTER_LEAVE( maxGroupSize );

    return currentTour;

} // TallyVotes::vote

void TallyVotes::done() {
    voters--;

    if ( voters < maxGroupSize ) {                                       // Detect Quorum Failure
        while ( !votingGroup.empty() ) {                                 // Flush all waiting voters
            votingGroup.signal();
        } // while
    } // if

} // TallyVotes::done