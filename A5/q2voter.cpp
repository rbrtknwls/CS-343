#include <iostream>
#include <uPRNG.h>

#include "q2voter.h"
#include "q2printer.h"


// Constructor for the voter
Voter::Voter( unsigned int id, unsigned int nvotes, TallyVotes & voteTallier, Printer & printer ) :
    id(id), nvotes(nvotes), voteTallier(&voteTallier), printer(&printer) {}

void Voter::main() {
    yield ( prng( 19 ) );                                  // Yield upto 19 times before starting
    try {
        _Enable{
                for ( unsigned int tourNum = 0; tourNum < nvotes; tourNum++ ) {
                    printer->print(id, Start);             // Print start
                    yield(prng(4));                        // Yield up to 4 times

                    TallyVotes::Ballot ballot = cast();    // Store the value of our vote
                    TallyVotes::Tour groupResult = voteTallier->vote(id, ballot);

                    yield(prng(4));                        // Yield up to 4 times
                    printer->print(id, Going, groupResult);// Print the group result
                }
        }
    } catch ( TallyVotes::Failed &failed ) {
        printer->print(id, Failed);                         // On failure print failure
    }


    // Print done if finished voting
    voteTallier->done(
#if defined(TASK )
            id
#endif
    );



}