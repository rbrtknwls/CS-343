#include "q3tallyVotes.h"


TallyVotes::TallyVotes( unsigned int voters, unsigned int group, Printer & printer ) :
        printer(&printer), groupNumber(group), voters(voters) {

    votes[0] = 0;
    votes[1] = 0;
    votes[2] = 0;
}

TallyVotes::TourKind TallyVotes::determineWinner() {
    if ( votes[0] >= votes[1] && votes[0] >= votes[2] ) { return Picture; }
    if ( votes[1] >= votes[0] && votes[1] >= votes[2] ) { return Statue; }
    return GiftShop;
}