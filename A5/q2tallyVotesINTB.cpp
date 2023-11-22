#include "q2tallyVotes.h"
#include "q2voter.h"
#include "q2printer.h"
#include <stdlib.h>

void TallyVotes::wait() {
    bench.wait();                                               // wait until signalled

    while ( rand() % 2 == 0 ) {                                 // multiple bargers allowed
       try {
           _Accept( TallyVotes::vote || TallyVotes::done ) {   // accept barging callers
           } _Else { }                                          // _Accept
       } catch( uMutexFailure::RendezvousFailure & ) {}
    }                                                           // while

}

void TallyVotes::signalAll() {                                  // also useful
    while ( ! bench.empty() ) bench.signal();                   // drain the condition
}


TallyVotes::Tour TallyVotes::vote( unsigned id, Ballot ballot ) {

    VOTER_ENTER( maxGroupSize );

    if ( voters < maxGroupSize ) {
        _Throw Failed();
    }

    unsigned int currentVoterNumber = newVoterNumber++;

    while ( currentVoterNumber > lastVoterInCurrentGroup ) {
        wait();
    }

    printer->print( id, Voter::Vote, ballot );

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

        signalAll();
        lastVoterInCurrentGroup += maxGroupSize;

        printer->print( id, Voter::Complete, currentTour );

    } else {
        printer->print( id, Voter::Block, currentNumberOfGroupMembers );

        wait();

        if ( voters < maxGroupSize ) { _Throw Failed(); }

        printer->print( id, Voter::Unblock, currentNumberOfGroupMembers - 1);
        
    }
    currentNumberOfGroupMembers--;

    if ( currentNumberOfGroupMembers == 0 ) {
        signalAll();
    }


    if ( voters < maxGroupSize ) { _Throw Failed(); }   // Quorum Failure

    VOTER_LEAVE( maxGroupSize );

    return currentTour;

}

void TallyVotes::done() {
    voters--;

    if ( voters < maxGroupSize ) { signalAll(); }
}