#ifndef CS_343_Q3TALLYVOTES_H
#define CS_343_Q3TALLYVOTES_H

#if defined( MC )					// mutex/condition solution
#include "BargingCheckVote.h"
class TallyVotes {
	// private declarations for this kind of vote-tallier
#elif defined( SEM )				// semaphore solution
#include "BargingCheckVote.h"
// includes for this kind of vote-tallier
class TallyVotes {
	// private declarations for this kind of vote-tallier
#elif defined( BAR )				// barrier solution
// includes for this kind of vote-tallier
_Cormonitor TallyVotes : public uBarrier {
	// private declarations for this kind of vote-tallier
#else
#error unsupported voter type
#endif
// common declarations
  public:							// common interface
    _Event Failed {};
    struct Ballot { unsigned int picture, statue, giftshop; };
    enum TourKind : char { Picture = 'p', Statue = 's', GiftShop = 'g' };
    struct Tour { TourKind tourkind; unsigned int groupno; };

    TallyVotes( unsigned int voters, unsigned int group, Printer & printer );
    Tour vote( unsigned int id, Ballot ballot );
    void done(
#if defined( MC ) || defined( BAR )
        unsigned int id
#endif
);

#endif
