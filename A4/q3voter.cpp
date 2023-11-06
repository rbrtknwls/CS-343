#include <iostream>
#include <uPRNG.h>

#include "q3voter.h"
#include "printer.h"

Voter::Voter( unsigned int id, unsigned int nvotes, TallyVotes & voteTallier, Printer & printer ) :
    id(id), nvotes(nvotes), voteTallier(&voteTallier), printer(&printer) {}

void Voter::main() {
    yield ( prng( 19 ) );
    for ( unsigned int tourNum = 0; tourNum < nvotes; tourNum++ ) {
        printer->print(id, Start);
        yield( prng(4) );
        printer->print(id, Start);
        yield( prng(4) );
        std::cout << "going on tour" << std::endl;
        std::cout << "end tour" << std::endl;
    }
}