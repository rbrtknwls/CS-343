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
    resume();
} // vote

void Player::terminate() {
    resume();
} // terminate

void Player::main() {
    suspend();
    for ( ;; ) {
        try {
            _Enable{
                if ( partner[0] == partner[1] ) {
                    break;
                }
                std::cout << id;
                potato.countdown();
                std::cout << " -> ";
                partner[prng(0, 1)]->toss();
            }
        } catch ( Potato::Explode &explode ) {
            std::cout << " is eliminated" << std::endl;

            if ( umpire->getId() == id ) {
                _Resume Election ( partner[1] ) _At *partner[1];
                try {
                    partner[1]->vote();
                } _CatchResume ( Election &election ) {
                    umpire = election.player;
                    std::cout << "HAIII";
                }
            }

            partner[1]->partner[0] = partner[0];
            partner[0]->partner[1] = partner[1];

            _Resume Terminate ( *this ) _At *umpire;
            umpire->terminate();
        } catch ( Terminate &terminate ) {
            //delete terminate.victim;

            std::cout << "U " << umpire->getId() << " ";
            potato.reset();
            partner[prng(0, 1)]->toss();

        } catch ( Election &election ) {
            std::cout << "ID: " << id << " voted" << std::endl;

            if ( election.player->getId() < id ) { _Resume Election ( this ) _At *partner[1]; }
            else { _Resume Election ( election ) _At *partner[1]; }

            partner[1]->vote();
        }

    }

}