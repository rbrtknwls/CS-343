#include "q3tallyVotes.h"
#include "q3voter.h"
#include "q3printer.h"

TallyVotes::Tour TallyVotes::vote( unsigned id, Ballot ballot ) {
    tallyVotes.P();

    VOTER_ENTER( maxGroupSize );

    if ( voters < maxGroupSize ) { _Throw Failed(); }

    printer->print( id, Voter::Vote, ballot );

    votes[0] += ballot.picture;
    votes[1] += ballot.statue;
    votes[2] += ballot.giftshop;
    currentNumberOfGroupMembers++;

    if (currentNumberOfGroupMembers == maxGroupSize) {

        currentTour.tourkind = determineWinner();
        currentTour.groupno = ++currentGroupNumber;

        votes[0] = 0;
        votes[1] = 0;
        votes[2] = 0;

        printer->print( id, Voter::Complete, currentTour );

    } else {
        printer->print( id, Voter::Block, currentNumberOfGroupMembers );

        votingGroup.P();

        printer->print( id, Voter::Unblock, currentNumberOfGroupMembers - 1);
    }


    VOTER_LEAVE( maxGroupSize );

    return currentTour;

    tallyVotes.V();
}