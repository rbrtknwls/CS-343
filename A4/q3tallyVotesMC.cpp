#include "q3tallyVotes.h"
#include "q3voter.h"
#include "q3printer.h"

TallyVotes::Tour TallyVotes::vote( unsigned id, Ballot ballot ) {
    tallyVotesLock.acquire();
    try {
        VOTER_ENTER( maxGroupSize );

        if ( votingGroupInProgress || !bargingLock.empty() ) {
            numberOfBarging++;

            printer->print( id, Voter::Barging, currentGroupNumber, currentNumberOfGroupMembers );

            bargingLock.wait( tallyVotesLock );
            numberOfBarging--;
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

            if ( !bargingLock.empty() ) { bargingLock.signal(); }
            else { votingGroupInProgress = false; }

            votingGroupLock.wait( tallyVotesLock );

            if ( !votingGroupInProgress && voters < maxGroupSize ) {
                if ( votingGroupLock.empty() ) { bargingLock.broadcast(); }
                _Throw Failed();
            }

            printer->print( id, Voter::Unblock, currentNumberOfGroupMembers - 1);
        }


        if ( --currentNumberOfGroupMembers == 0 ) {
            if ( bargingLock.empty() ) { votingGroupInProgress = false; }
            else { bargingLock.signal(); }
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

        if ( voters < maxGroupSize ) {
            if ( !votingGroupLock.empty() ) { votingGroupLock.broadcast(); }
            else { bargingLock.broadcast(); }

        }

        if ( bargingLock.empty() ) { votingGroupInProgress = false; }

    } _Finally {
            tallyVotesLock.release();
    }
}