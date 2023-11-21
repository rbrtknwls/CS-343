#ifndef CS_343_Q3TALLYVOTES
#define CS_343_Q3TALLYVOTES

_Monitor Printer;

#if defined( EXT ) // external scheduling monitor solution
// includes for this kind of vote-tallier
_Monitor TallyVotes {
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
#if defined( TASK )
        unsigned int id
#endif
    );
  private:
    TourKind determineWinner();
    Tour currentTour;
};

#endif