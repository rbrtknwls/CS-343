#include "q2tallyVotes.h"


// This is the implementation of generic methods for tally Votes

TallyVotes::TallyVotes( unsigned int voters, unsigned int group, Printer & printer ) :
        printer(&printer), maxGroupSize(group), voters(voters) {

    // Set all the votes to 0
    votes[0] = 0;
    votes[1] = 0;
    votes[2] = 0;

    currentGroupNumber = 0;
}

// Method for determining winner, biases included!
TallyVotes::TourKind TallyVotes::determineWinner() {
    if ( votes[0] >= votes[1] && votes[0] >= votes[2] ) { return Picture; }
    if ( votes[1] >= votes[0] && votes[1] >= votes[2] ) { return Statue; }
    return GiftShop;
}