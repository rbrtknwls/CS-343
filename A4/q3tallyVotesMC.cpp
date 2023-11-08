#include "q3tallyVotes.h"
#include "q3voter.h"
#include "q3printer.h"

TallyVotes::Tour TallyVotes::vote( unsigned id, Ballot ballot ) {
    tallyVotesLock.acquire();
    try {

        if ( votingGroupInProgress ) {
            bargingLock.wait( tallyVotesLock );
        }


        votes[0] += ballot.picture;
        votes[1] += ballot.statue;
        votes[2] += ballot.giftshop;
        currentNumberOfGroupMembers++;

        Tour currentTour;
        if (currentNumberOfGroupMembers == maxGroupSize) {
            votingGroupInProgress = true;

            currentTour.tourkind = determineWinner();
            currentTour.groupno = ++currentGroupNumber;

            votes[0] = 0;
            votes[1] = 0;
            votes[2] = 0;

            printer->print(id, voter::Complete);

        } else {
            printer->print(id, voter::Block, currentNumberOfGroupMembers);
            votingGroupLock.wait( tallyVotesLock );
            printer->print(id, voter::Unblock, --currentNumberOfGroupMembers);
        }

        if ( currentNumberOfGroupMembers == 0) {
            votingGroupInProgress = false;
            bargingLock.broadcast();
        } else {
            votingGroupLock.signal();
        }

        return currentTour;

    } _Finally {
        tallyVotesLock.release();
    }
}

void TallyVotes::done( unsigned id ) {
    printer->print(id, Voter::Terminated );
    voters--;
    if (voters == 0) { printer->print(id, Voter::Terminated ); }
}