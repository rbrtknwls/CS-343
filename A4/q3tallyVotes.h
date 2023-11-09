#ifndef CS_343_Q3TALLYVOTES
#define CS_343_Q3TALLYVOTES

_Monitor Printer;

#if defined( MC )					// mutex/condition solution
#include "BargingCheckVote.h"
// includes for this kind of vote-tallier
class TallyVotes {
    uOwnerLock tallyVotesLock;         // Owner Lock
    uCondLock votingGroupLock;         // Voting Group Lock
    uCondLock bargingLock;             // Barging Lock

    bool votingGroupInProgress = false;// Signal
    BCHECK_DECL;

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
    Printer * printer;
    unsigned int maxGroupSize;
    unsigned int numberOfBarging;
    unsigned int currentGroupNumber;
    unsigned int voters;
    unsigned int votes[3];
    unsigned int currentNumberOfGroupMembers;

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
  private:
    TourKind determineWinner();
    Tour currentTour;
};

#endif