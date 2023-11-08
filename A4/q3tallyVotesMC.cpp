#include "q3tallyVotes.h"
#include "q3voter.h"

TallyVotes::Tour TallyVotes::vote( unsigned id, Ballot ballot ) {
    votes[0] += ballot.picture;
    votes[1] += ballot.statue;
    votes[2] += ballot.giftshop;
    currentNumberOfGroupMembers++;

    if ( currentNumberOfGroupMembers == voters ) {
        if (id == 1) {

        }
        votes[0] = 0;
        votes[1] = 0;
        votes[2] = 0;
    }
    TourKind winner = determineWinner();
    Tour newTour;
    newTour.tourkind = winner;
    newTour.groupno = groupNumber;
    return newTour;
}

void TallyVotes::done( unsigned id ) {
    printer->print(id, Voter::terminate );
    voters--;
    if (voters == 0) { printer->print(id, Voter::terminate ); }
}