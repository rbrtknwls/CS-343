#include <uPRNG.h>
#include "q2player.h"
#include "q2potato.h"

Player::Player( PRNG & prng, unsigned int id, Potato & potato ) : prng ( prng ), id ( id ), potato ( potato ) { }

