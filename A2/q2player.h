#ifndef CS_343_PLAYER_H
#define CS_343_PLAYER_H

#include "q2potato.h"

_Coroutine Player {
    PRNG & prng;
    int id;
    Potato & potato;
    _Event Terminate {
      public:
        Player & victim;					// delete player
        Terminate( Player & victim ) : victim( victim ) {}
    };
    _Event Election {
      public:
        Player * player;					// highest player id seen so far
        Election( Player * player ) : player( player ) {}
    };
    Player * partner[2];					// left and right player
    void main();
    void vote();         					// resume partner to vote
    void terminate();						// resume umpire
  public:
    static Player * umpire;					// current umpire
    Player( PRNG & prng, unsigned int id, Potato & potato );
    void init( Player & lp, Player & rp );	// supply partners
    int getId();							// player id
    void toss();							// tossed potato

};
#endif
