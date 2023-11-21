#include "q2tallyVotes.h"
#include "q2voter.h"
#include "q2printer.h"


TallyVotes::Tour TallyVotes::vote( unsigned id, Ballot ballot ) {

    printer->print( id, Voter::Vote, ballot );

    votes[0] += ballot.picture;
    votes[1] += ballot.statue;
    votes[2] += ballot.giftshop;

    return currentTour;

}

void TallyVotes::done( ) {
    printer->print(id, Voter::Terminated);
    voters--;

    if ( voters < maxGroupSize ) {

    }
}