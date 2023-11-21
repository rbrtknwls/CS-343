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
#include <uSemaphore.h>
// includes for this kind of vote-tallier
class TallyVotes {
	// private declarations for this kind of vote-tallier
    uSemaphore tallyVotes;                           // Set to open at start
    uSemaphore votingGroup = uSemaphore( 0 );        // Set to locked at start
    uSemaphore barging;                              // Set to open at start

    BCHECK_DECL;
#elif defined( BAR )				// barrier solution
#include <uBarrier.h>
// includes for this kind of vote-tallier
_Cormonitor TallyVotes : public uBarrier {
	// private declarations for this kind of vote-tallier
#else
    #error unsupported voter type
#endif
    Printer * printer;
    unsigned int maxGroupSize;                        // Stores the size of the voting group
    unsigned int currentGroupNumber;                  // Stores the current group number
    unsigned int voters;                              // Stores the number of voters
    unsigned int votes[3];                            // Holds the sum of votes for voters
    unsigned int currentNumberOfGroupMembers;         // Stores the number of voters in current group

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