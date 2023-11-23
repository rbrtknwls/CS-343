#include "q2tallyVotes.h"
#include "q2voter.h"
#include "q2printer.h"
#include "AutomaticSignal.h"
#include <stdlib.h>

/*
 * Implementation of TallyVotes done using an automatic monitor.
 */

TallyVotes::Tour TallyVotes::vote( unsigned id, Ballot ballot ) {

    VOTER_ENTER( maxGroupSize );

    if ( voters < maxGroupSize ) {                                     // Quorum failure
        EXIT();
        _Throw Failed();
    } // if


    printer->print( id, Voter::Vote, ballot );

    votes[0] += ballot.picture;
    votes[1] += ballot.statue;
    votes[2] += ballot.giftshop;

    currentNumberOfGroupMembers++;

    if ( currentNumberOfGroupMembers == maxGroupSize ) {                // Called for last member in group
        currentTour.tourkind = determineWinner();
        currentTour.groupno = ++currentGroupNumber;

        // Reset the number of votes
        votes[0] = 0;
        votes[1] = 0;
        votes[2] = 0;

        onTour = true;                                                  // Set predicate to be true
        printer->print( id, Voter::Complete, currentTour );

    } else {
        printer->print( id, Voter::Block, currentNumberOfGroupMembers );

        WAITUNTIL(onTour, ,);                                           // Wait for predicate

        printer->print( id, Voter::Unblock, currentNumberOfGroupMembers - 1);

    } // if
    currentNumberOfGroupMembers--;

    if ( currentNumberOfGroupMembers == 0 ) { onTour = false; }        // Update predicate
    EXIT();
    if ( voters < maxGroupSize ) { _Throw Failed(); }                  // Quorum Failure

    VOTER_LEAVE( maxGroupSize );

    return currentTour;

} // TallyVotes::Vote

void TallyVotes::done() {
    voters--;

    if ( voters < maxGroupSize ) { onTour = true; }                  // Quorum Failure
    EXIT();
} // TallyVotes::Done