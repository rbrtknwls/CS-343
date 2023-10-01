#ifndef CS_343_Q2_H
#define CS_343_Q2_H

class Potato {
    PRNG prng;
    int currentTicks;
  public:
    _Event Explode {};
    Potato( PRNG & prng, unsigned int maxTicks = 10 ): prng( prng ) currentTicks( maxTicks ) {}
    void reset( unsigned int maxTicks = 10 ): currentTicks( maxTicks ) {}
    void countdown();
};

_Coroutine Player {
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
    void vote();							// resume partner to vote
    void terminate();						// resume umpire
  public:
    static Player * umpire;					// current umpire
    Player( PRNG & prng, unsigned int id, Potato & potato );
    void init( Player & lp, Player & rp );	// supply partners
    int getId();							// player id
    void toss();							// tossed potato

};

#endif //CS_343_Q2_H
