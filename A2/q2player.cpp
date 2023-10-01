#include <iostream>
#include <uPRNG.h>

#include "q2player.h"
#include "q2potato.h"

Player::Player( PRNG & prng, unsigned int id, Potato & potato ) : prng ( prng ), id ( id ), potato ( potato ) { }

void Player::init( Player & lp, Player & rp ) {
    std::cout << "ID: " << id << "[ L: " << lp.getId() << ", R: " << rp.getId() << " ]" << std::endl;

    partner[0] = &lp;
    partner[1] = &rp;
} // init

int Player::getId() { return id; }

void Player::toss() {
    std::cout << "TOSS" << std::endl;
} // toss


void Player::vote() {
    std::cout << "TOSS" << std::endl;
} // vote

void Player::terminate() {
    std::cout << "TOSS" << std::endl;
} // terminate

void Player::main() {
    std::cout << "TOSS" << std::endl;
} // main