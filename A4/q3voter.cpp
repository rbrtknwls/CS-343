#include <iostream>
#include <uPRNG.h>

#include "q3voter.h"

Voter::Voter( unsigned int id, unsigned int nvotes, TallyVotes & voteTallier, Printer & printer ) :
    id(id), nvotes(nvotes), voteTallier(&voteTallier), printer(&printer) {}

void Voter::main() {
    yield ( prng( 19 ) );
    for ( unsigned int tourNum = 0; tourNum < nvotes; tourNum++ ) {
        std::cout << "start" << std::endl;
        yield( prng(4) );
        std::cout << "vote" << std::endl;
        yield( prng(4) );
        std::cout << "going on tour" << std::endl;
        std::cout << "end tour" << std::endl;
    }
}