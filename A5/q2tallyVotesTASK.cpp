#include "q2tallyVotes.h"
#include "q2voter.h"
#include "q2printer.h"

#include <stdlib.h>

void TallyVotes::main() {
    for ( ;; ) {
        printer->print( id, Voter::Vote, ballot );
    }
}

TallyVotes::Tour TallyVotes::vote( unsigned id, Ballot ballot ) {

    VOTER_ENTER( maxGroupSize );

    if ( voters < maxGroupSize ) {
        EXIT();
        _Throw Failed();
    }


    printer->print( id, Voter::Vote, ballot );

    votes[0] += ballot.picture;
    votes[1] += ballot.statue;
    votes[2] += ballot.giftshop;

    currentNumberOfGroupMembers++;

    if ( currentNumberOfGroupMembers == maxGroupSize ) {
        currentTour.tourkind = determineWinner();
        currentTour.groupno = ++currentGroupNumber;

        // Reset the number of votes
        votes[0] = 0;
        votes[1] = 0;
        votes[2] = 0;

        onTour = true;
        printer->print( id, Voter::Complete, currentTour );

    } else {
        printer->print( id, Voter::Block, currentNumberOfGroupMembers );

        WAITUNTIL(onTour, ,);

        printer->print( id, Voter::Unblock, currentNumberOfGroupMembers - 1);

    }
    currentNumberOfGroupMembers--;

    if ( currentNumberOfGroupMembers == 0 ) { onTour = false; }
    EXIT();
    if ( voters < maxGroupSize ) { _Throw Failed(); }   // Quorum Failure

    VOTER_LEAVE( maxGroupSize );

    return currentTour;

}

void TallyVotes::done( unsigned int id ) {
    voters--;

    if ( voters < maxGroupSize ) { onTour = true; }
    EXIT();
}