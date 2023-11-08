#include "q3tallyVotes.h"
#include "q3voter.h"
#include "q3printer.h"

TallyVotes::Tour TallyVotes::vote( unsigned id, Ballot ballot ) {
    tallyVotesLock.acquire();
    try {
        votes[0] += ballot.picture;
        votes[1] += ballot.statue;
        votes[2] += ballot.giftshop;
        currentNumberOfGroupMembers++;

        if (currentNumberOfGroupMembers == groupNumber) {
            if (id == 1) {

            }
            votes[0] = 0;
            votes[1] = 0;
            votes[2] = 0;
        } else {
            votingGroupLock.wait(tallyVotesLock);
        }
        TourKind winner = determineWinner();
        Tour newTour;
        newTour.tourkind = winner;
        newTour.groupno = groupNumber;
        return newTour;
    } _ Finally {
        tallyVotesLock.release();
    }
}

void TallyVotes::done( unsigned id ) {
    printer->print(id, Voter::Terminated );
    voters--;
    if (voters == 0) { printer->print(id, Voter::Terminated ); }
}