#include "q2tallyVotes.h"
#include "q2voter.h"
#include "q2printer.h"
#include <stdlib.h>

/*
 * Implementation of TallyVotes done using a Java Monitor.
 */

void TallyVotes::wait() {
    bench.wait();                                               // wait until signalled

    while ( rand() % 2 == 0 ) {                                 // multiple bargers allowed
       try {
           _Accept( TallyVotes::vote || TallyVotes::done ) {    // accept barging callers
           } _Else { }                                          // _Accept
       } catch( uMutexFailure::RendezvousFailure & ) {}
    }                                                           // while

} // TallyVotes::wait

void TallyVotes::signalAll() {                                  // also useful
    while ( ! bench.empty() ) bench.signal();                   // drain the condition
} // TallyVotes::signalAll


TallyVotes::Tour TallyVotes::vote( unsigned id, Ballot ballot ) {

    VOTER_ENTER( maxGroupSize );

    if ( voters < maxGroupSize ) { _Throw Failed(); }            // Catch Quorum Failure

    unsigned int currentVoterNumber = newVoterNumber++;          // Keep track of current voter Id

    if ( currentVoterNumber >= lastVoterInCurrentGroup ) {       // Stop any bargers (id > last in group)
        numberOfBargers++;

        while ( currentVoterNumber >= lastVoterInCurrentGroup ) {
            printer->print(id, Voter::Barging, numberOfBargers );
            wait();
        } // while

        numberOfBargers--;
    }

    printer->print( id, Voter::Vote, ballot );

    // Update votes with voter preferences
    votes[0] += ballot.picture;
    votes[1] += ballot.statue;
    votes[2] += ballot.giftshop;

    currentNumberOfGroupMembers++;

    if ( currentNumberOfGroupMembers == maxGroupSize ) {
        currentTour.tourkind = determineWinner();
        currentTour.groupno = ++currentGroupNumber;

        // Reset the number of votes
        votes[0] = 0;
        votes[1] = 0;
        votes[2] = 0;


        signalAll();                                            // Wake up all the waiting voters

        printer->print( id, Voter::Complete, currentTour );

    } else {
        printer->print( id, Voter::Block, currentNumberOfGroupMembers );

        wait();                                                 // Wait for the group to be made

        printer->print( id, Voter::Unblock, currentNumberOfGroupMembers - 1);

    } // if
    currentNumberOfGroupMembers--;

    if ( currentNumberOfGroupMembers == 0 ) {                   // Release all the barging Tasks
        lastVoterInCurrentGroup += maxGroupSize;                // Update the id of the last voter in group
        signalAll();
    } // if


    if ( voters < maxGroupSize ) { _Throw Failed(); }            // Quorum Failure

    VOTER_LEAVE( maxGroupSize );

    return currentTour;

} // TallyVotes::vote

void TallyVotes::done() {
    voters--;

    if ( voters < maxGroupSize ) { signalAll(); }                 // Quorum Failure
}  // TallyVotes::done