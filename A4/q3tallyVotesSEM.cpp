#include "q3tallyVotes.h"
#include "q3voter.h"
#include "q3printer.h"

/*
 * Semaphore implementation of tally voters, this contains both the vote method and the done method. All the other
 *  methods that are needed for tally votes are implemented in the generic tallyVotes.cpp
 */

TallyVotes::Tour TallyVotes::vote( unsigned id, Ballot ballot ) {

    barging.P();                                       // Grab the barging semaphore (prevention)
    tallyVotes.P();                                    // Grab the overall semaphore

    VOTER_ENTER( maxGroupSize );

    if ( voters < maxGroupSize ) {                     // Quorum Failure
        barging.V();
        _Throw Failed();
    }

    printer->print( id, Voter::Vote, ballot );

    // Sum up the votes given the voters preferences
    votes[0] += ballot.picture;
    votes[1] += ballot.statue;
    votes[2] += ballot.giftshop;

    currentNumberOfGroupMembers++;
    if (currentNumberOfGroupMembers == maxGroupSize) { // Last member of the group
        currentTour.tourkind = determineWinner();
        currentTour.groupno = ++currentGroupNumber;

        votes[0] = 0;
        votes[1] = 0;
        votes[2] = 0;

        printer->print( id, Voter::Complete, currentTour );

    } else {
        printer->print( id, Voter::Block, currentNumberOfGroupMembers );

        barging.V();                                 // Let values get the barging semaphore
        tallyVotes.V();                              // Let values get the tally votes semaphore
        votingGroup.P();                             // Wait on voting group
        tallyVotes.P();                              // Get tally group

        printer->print( id, Voter::Unblock, currentNumberOfGroupMembers - 1);
    }
    currentNumberOfGroupMembers--;

    // If our voting group is non empty, we release one else we let barging in
    if ( !votingGroup.empty() ) { votingGroup.V(); } else { barging.V(); }
    VOTER_LEAVE( maxGroupSize );
    tallyVotes.V();                                  // release tally vote

    if ( voters < maxGroupSize ) { _Throw Failed(); }// Quorum failure
    return currentTour;

}

void TallyVotes::done () {
    voters--;                                        // reduce the number of votes
    if ( voters < maxGroupSize ) {
        if (!votingGroup.empty()) {
            votingGroup.V();                         // Let voting group members fail first
        } else {
            barging.V();                             // if no voting group, let barging fail
        }
    }
}