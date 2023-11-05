#include "q3tallyVotes.h"

TallyVotes::TallyVotes( unsigned int voters, unsigned int group, Printer & printer ) :
    printer(&printer), groupNumber(group), voters(voters) {}