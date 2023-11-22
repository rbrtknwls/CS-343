#include "q2tallyVotes.h"
#include "q2voter.h"
#include "q2printer.h"



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

        votingGroup.wait();
        if ( voters < maxGroupSize ) { _Throw Failed(); }

        printer->print( id, Voter::Unblock, currentNumberOfGroupMembers - 1);
    }
    currentNumberOfGroupMembers--;

    votingGroup.signal();

    if ( voters < maxGroupSize ) { _Throw Failed(); }   // Quorum Failure
    return currentTour;

}

void TallyVotes::done() {
    voters--;

    if ( voters < maxGroupSize ) {
        while ( !votingGroup.empty() ) {
            votingGroup.signal();
        }
    }
}