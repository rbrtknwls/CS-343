#include "q3tallyVotes.h"
#include "q3voter.h"
#include "q3printer.h"

/*
 * Lock implementation of tally voters, this contains both the vote method and the done method. All the other methods
 *  that are needed for tally votes are implemented in the generic tallyVotes.cpp
 */

TallyVotes::Tour TallyVotes::vote( unsigned id, Ballot ballot ) {
    tallyVotesLock.acquire();                                   // Acquire the owner lock
    try {
        VOTER_ENTER( maxGroupSize );                            // Start of the mutual exclusion

        /*
         * Barging can occur if we have values waiting to barge, or if the current group is being "sent off"
         *  in either case we will catch the barging case and stop them in their tracks
         */
        if ( votingGroupInProgress || !bargingLock.empty() ) {
            printer->print( id, Voter::Barging, currentGroupNumber, currentNumberOfGroupMembers );
            bargingLock.wait( tallyVotesLock );
        }

        if ( voters < maxGroupSize ) { _Throw Failed(); }      // Quorum failure

        printer->print( id, Voter::Vote, ballot );

        // Update sum of votes and add member to currentNumberOfGroupMembers
        votes[0] += ballot.picture;
        votes[1] += ballot.statue;
        votes[2] += ballot.giftshop;
        currentNumberOfGroupMembers++;

        if (currentNumberOfGroupMembers == maxGroupSize) {     // Apply to only last member of group
            votingGroupInProgress = true;                      // Start process of voting

            currentTour.tourkind = determineWinner();          // Set tour to winner
            currentTour.groupno = ++currentGroupNumber;        // Update the group number and set it

            // Reset the number of votes
            votes[0] = 0;
            votes[1] = 0;
            votes[2] = 0;

            printer->print( id, Voter::Complete, currentTour );

        } else {

            printer->print( id, Voter::Block, currentNumberOfGroupMembers );

            // If barging lock is not empty, we want to release one otherwise we reset the flag
            if ( !bargingLock.empty() ) { bargingLock.signal(); }
            else { votingGroupInProgress = false; }

            votingGroupLock.wait( tallyVotesLock );

            printer->print( id, Voter::Unblock, currentNumberOfGroupMembers - 1);
        }


        // If last member of the group alert the barging tasks to come in, else keep letting voting group in
        if ( --currentNumberOfGroupMembers == 0 ) {
            if ( bargingLock.empty() ) { votingGroupInProgress = false; }
            else { bargingLock.signal(); }
        } else {
            votingGroupLock.signal();
        }

        // If the voters < maxGroupSize and we arent currently voting, then we throw an error
        if ( !votingGroupInProgress && voters < maxGroupSize ) {
            if ( votingGroupLock.empty() ) { bargingLock.broadcast(); }
            else { votingGroupLock.signal(); }
            _Throw Failed();
        }

        VOTER_LEAVE( maxGroupSize );

        return currentTour;

    } _Finally {
        tallyVotesLock.release();                     // Always release the owner lock when done
    }
}

void TallyVotes::done( unsigned id ) {
    tallyVotesLock.acquire();                         // Grab the owner lock
    try {
        printer->print(id, Voter::Terminated);
        voters--;                                     // Reduce the number of voters

        // Quorum failure, should have the voting group voters fail first then the barging tasks
        if ( voters < maxGroupSize ) {
            if ( !votingGroupLock.empty() ) { votingGroupLock.signal(); }
            else { bargingLock.broadcast(); }
        }

    } _Finally {
        tallyVotesLock.release();                     // Always release this lock
    }
}