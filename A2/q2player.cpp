#include <iostream>
#include <uPRNG.h>

#include "q2player.h"

Player* Player::umpire;

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
    resume();
} // terminate

void Player::main() {
    suspend();
    for ( ;; ) {
        try {
            _Enable{
                std::cout << id;
                potato.countdown();
                std::cout << " -> ";
                partner[prng(0, 1)]->toss();
            }
        } catch ( Potato::Explode &explode ) {
            std::cout << " is eliminated" << std::endl;

            partner[1]->partner[0] = partner[0];
            partner[0]->partner[1] = partner[1];

            _Resume Terminate ( *this ) _At *umpire;
            umpire->terminate();
        } catch ( Terminate &terminate ) {
            delete terminate.victim;

            std::cout << "U";
            potato->reset();
            partner[prng(0, 1)]->toss();
        }

    }

}