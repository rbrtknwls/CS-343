#include "q3voter.h"

Voter::Voter( unsigned int id, unsigned int nvotes, TallyVotes & voteTallier, Printer & printer ) :
    id(id), nvotes(nvotes), voteTallier(voteTallier), printer(printer) {}