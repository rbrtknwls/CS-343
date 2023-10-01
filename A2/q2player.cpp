#include <iostream>
#include <uPRNG.h>

#include "q2player.h"


Player::Player( PRNG & prng, unsigned int id, Potato & potato ) : prng ( prng ), id ( id ), potato ( potato ) {

    std::cout << "MADE";
}
