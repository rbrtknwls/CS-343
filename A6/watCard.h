#ifndef CS_343_WATCARD_H
#define CS_343_WATCARD_H

#include <uFuture.h>

class WATCard {
    WATCard( const WATCard & ) = delete;
    WATCard( const WATCard && ) = delete;
    WATCard & operator=( const WATCard & ) = delete;
    WATCard & operator=( const WATCard && ) = delete;
    unsigned int balance = 0;

  public:
    typedef Future_ISM<WATCard *> FWATCard;
    WATCard();
    void deposit( unsigned int amount );
    void withdraw( unsigned int amount );
    unsigned int getBalance();
};

#endif //CS_343_WATCARD_H
