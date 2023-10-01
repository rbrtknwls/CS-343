#include <iostream>
#include <uPRNG.h>

#include "q2player.h"
#include "q2potato.h"

Player::Player( PRNG & prng, unsigned int id, Potato & potato ) : prng ( prng ), id ( id ), potato ( potato ) {

    std::cout << "MADE";

}

void Player::init( Player & lp, Player & rp ) {
    std::cout << "SILLYYYY";
}

int Player::getId() { return id; }

void Player::toss() {
    std::cout << "TOSS" << std::endl;
}