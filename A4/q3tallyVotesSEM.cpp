#include "q3tallyVotes.h"
#include "q3voter.h"
#include "q3printer.h"

TallyVotes::Tour TallyVotes::vote( unsigned id, Ballot ballot ) {

    barging.P();
    tallyVotes.P();

    VOTER_ENTER( maxGroupSize );

    if ( voters < maxGroupSize ) {
        barging.V();
        _Throw Failed();
    }

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

        barging.V();
        tallyVotes.V();
        votingGroup.P();
        tallyVotes.P();

        printer->print( id, Voter::Unblock, currentNumberOfGroupMembers - 1);
    }
    currentNumberOfGroupMembers--;

    if ( !votingGroup.empty() ) { votingGroup.V(); } else { barging.V(); }
    VOTER_LEAVE( maxGroupSize );
    tallyVotes.V();
    
    if ( voters < maxGroupSize ) { _Throw Failed(); }
    return currentTour;

}

void TallyVotes::done () {
    voters--;
    if ( voters < maxGroupSize ) {
        if (!votingGroup.empty()) {
            votingGroup.V();
        } else {
            barging.V();
        }
    }
}