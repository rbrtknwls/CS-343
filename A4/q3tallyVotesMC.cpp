#include "q3tallyVotes.h"
#include "q3voter.h"
#include "q3printer.h"

TallyVotes::Tour TallyVotes::vote( unsigned id, Ballot ballot ) {
    tallyVotesLock.acquire();
    try {
        VOTER_ENTER( maxGroupSize );

        if ( votingGroupInProgress ) {
            //bargingLock.wait( tallyVotesLock );
        }

        if ( voters < maxGroupSize ) { _Throw Failed(); }

        printer->print( id, Voter::Vote, ballot );

        votes[0] += ballot.picture;
        votes[1] += ballot.statue;
        votes[2] += ballot.giftshop;
        currentNumberOfGroupMembers++;

        if (currentNumberOfGroupMembers == maxGroupSize) {
            votingGroupInProgress = true;

            currentTour.tourkind = determineWinner();
            currentTour.groupno = ++currentGroupNumber;

            votes[0] = 0;
            votes[1] = 0;
            votes[2] = 0;

            printer->print( id, Voter::Complete, currentTour );

        } else {
            printer->print( id, Voter::Block, currentNumberOfGroupMembers );
            votingGroupLock.wait( tallyVotesLock );

            if ( voters < maxGroupSize && !votingGroupInProgress ) { _Throw Failed(); }

            printer->print( id, Voter::Unblock, currentNumberOfGroupMembers - 1);
        }

        if ( --currentNumberOfGroupMembers == 0) {
            votingGroupInProgress = false;
            //bargingLock.broadcast();
        } else {
            votingGroupLock.signal();
        }

        VOTER_LEAVE( maxGroupSize );

        return currentTour;

    } _Finally {
        tallyVotesLock.release();
    }
}

void TallyVotes::done( unsigned id ) {
    tallyVotesLock.acquire();
    try {
        printer->print(id, Voter::Terminated);
        voters--;

        if (voters < maxGroupSize && !votingGroupInProgress) {
            votingGroupLock.broadcast();
        }

        if (voters == 0) { printer->print(id, Voter::Terminated); }
    } _Finally {
            tallyVotesLock.release();
    }
}