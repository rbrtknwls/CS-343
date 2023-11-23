#include "q2tallyVotes.h"
#include "q2voter.h"
#include "q2printer.h"

#include <stdlib.h>

void TallyVotes::main() {

    for ( ;; ) {
        try {
            _Accept ( ~TallyVotes ) {

                break;

            } or _Accept( TallyVotes::vote ) {

                if ( voters < maxGroupSize ) { _Throw Failed(); }

                printer->print( currentId, Voter::Vote, currentBallot );

                votes[0] += currentBallot.picture;
                votes[1] += currentBallot.statue;
                votes[2] += currentBallot.giftshop;

                currentNumberOfGroupMembers++;

                if ( currentNumberOfGroupMembers == maxGroupSize ) {
                    currentTour.tourkind = determineWinner();
                    currentTour.groupno = ++currentGroupNumber;

                    // Reset the number of votes
                    votes[0] = 0;
                    votes[1] = 0;
                    votes[2] = 0;

                    printer->print( currentId, Voter::Complete, currentTour );

                    while ( !bench.empty() ) {
                        unsigned int voterToWake = bench.front();
                        printer->print( voterToWake, Voter::States::Unblock, currentNumberOfGroupMembers - 1 );
                        bench.signalBlock();
                    }


                } else {
                    printer->print( currentId, Voter::Block, currentNumberOfGroupMembers );

                }


            } or _Accept( TallyVotes::done ) {

                bench.signalBlock();
            }
        } catch ( uMutexFailure::RendezvousFailure& ) {

        }
    }
}

TallyVotes::Tour TallyVotes::vote( unsigned id, Ballot ballot ) {
    printer->print( 0, Voter::Terminated );
    currentBallot = ballot;
    currentId = id;

    bench.wait( id );

    currentNumberOfGroupMembers--;

    if ( voters < maxGroupSize ) { _Throw Failed(); }

    return currentTour;

}

void TallyVotes::done( unsigned int id ) {

    currentId = id;
    voters--;
}