#include <iostream>
#include <uPRNG.h>

#include "q2player.h"

Player::Player( PRNG & prng, unsigned int id, Potato & potato ) : prng ( prng ), id ( id ), potato ( potato ) { }

void Player::init( Player & lp, Player & rp ) {
    partner[0] = &lp;
    partner[1] = &rp;
    resume();
} // init

int Player::getId() { return id; }

void Player::toss() {
    resume();
} // toss


void Player::vote() {
    std::cout << "TOSS" << std::endl;
} // vote

void Player::terminate() {
    std::cout << "TOSS" << std::endl;
} // terminate

void Player::main() {
    suspend();
    for ( ;; ) {
        std::cout << id;
        try {
            _Enable{
                potato.countdown();
                std::cout << " -> ";
                partner[prng(0, 1)]->toss();
            }
        } catch ( Potato::Explode &explode ) {
            std::cout << id << std::endl;
            suspend();
        }
    }

}