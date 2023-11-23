#include "q2tallyVotes.h"
#include "q2voter.h"
#include "q2printer.h"

#include <stdlib.h>

/*
 * Implementation of TallyVotes done using a Task.
 */

void TallyVotes::main() {

    for ( ;; ) {
        try {
            _Accept ( ~TallyVotes ) {

                break;

            } or _Accept( TallyVotes::vote ) {

                if ( voters < maxGroupSize ) { _Throw Failed(); }      // Quorum Failure

                printer->print( currentId, Voter::Vote, currentBallot );

                // Update votes with the current voter
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

                    while ( !bench.empty() ) {              // Wake everyone up who is waiting
                        unsigned int voterToWake = bench.front();
                        printer->print( voterToWake, Voter::States::Unblock, currentNumberOfGroupMembers - 1 );
                        bench.signalBlock();
                    }


                } else {

                    printer->print( currentId, Voter::Block, currentNumberOfGroupMembers );

                } // if


            } or _Accept( TallyVotes::done ) {

                printer->print( currentId, Voter::Terminated );

                if ( voters < maxGroupSize ) {          // Quorum failure

                    while ( !bench.empty() ) {          // If there are voters left to wake up
                        unsigned int voterToWake = bench.front();
                        printer->print( voterToWake, Voter::States::Unblock, currentNumberOfGroupMembers - 1 );
                        bench.signalBlock();
                    } // while

                } else {

                    if ( !bench.empty() ) {              // If theres a voter that could have gone
                        unsigned int voterThatIsBlocked = bench.front();
                        // That voter could've progressed, but instead we did Done, so print done.
                        printer->print( voterThatIsBlocked, Voter::Done);
                    } // if

                } // if

            } // _Accept( Done )
        } catch ( uMutexFailure::RendezvousFailure& ) {

            while ( !bench.empty() ) {                     // While there are voters left
                unsigned int voterToWake = bench.front();  // Get the next voter whos waiting to go
                printer->print( voterToWake, Voter::States::Unblock, currentNumberOfGroupMembers - 1 );
                bench.signalBlock();                       // Wake up the voter
            } // while

        } // try
    } // for
} // TallyVotes::main

TallyVotes::Tour TallyVotes::vote( unsigned id, Ballot ballot ) {

    currentBallot = ballot;                                 // Save the ballot for main
    currentId = id;                                         // Save the id for main

    if ( voters < maxGroupSize ) { _Throw Failed(); }       // Quorum failure

    bench.wait( id );                                       // Store the id so we can be woken up

    if ( voters < maxGroupSize ) { _Throw Failed(); }       // Quorum failure
    currentNumberOfGroupMembers--;


    return currentTour;

} // TallyVotes::vote

void TallyVotes::done( unsigned int id ) {
    currentId = id;                                      // Store the id from main
    voters--;
} // TallyVotes::done