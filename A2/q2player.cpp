#include <iostream>
#include <uPRNG.h>

#include "q2player.h"

Player* Player::umpire;                                                   // Set a static reference to the umpire


Player::Player( PRNG & prng, unsigned int id, Potato & potato ) : prng ( prng ), id ( id ), potato ( potato ) { }

void Player::init( Player & lp, Player & rp ) {
    partner[0] = &lp;                                                     // Create a pointer to the left player
    partner[1] = &rp;                                                     // Create a pointer to the right player
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

/*
 *  This is the main function for player, in it we do the following:
 *      1) Pass the potato to the next player and count down the player
 *      2) Handle the potato exploding, hand over control to umpire
 *      3) If umpire exploded elect a new umpire
 *      4) Check to see if there are any players left
 */
void Player::main() {
    suspend();
    for ( ;; ) {
        try {
            _Enable {

              if ( partner[0] == this ) {                                   // Determine if player is only one left
                    std::cout << id << " wins the Match!" << std::endl;
                    break;
              } // if

                std::cout << id;
                potato.countdown();                                         // Can throw the explosion exception
                std::cout << " -> ";
                partner[prng(0, 1)]->toss();                                // Resume the next player in the game
            } // Enable
        } catch ( Potato::Explode &explode ) {
            std::cout << " is eliminated" << std::endl;

            if ( umpire->getId() == id ) {                                  // Check to see if the player is the umpire
                std::cout << "E " << id;
                _Resume Election ( partner[1] ) _At *partner[1];            // Start a new Election traveling right
                try {
                    _Enable{
                        partner[1]->vote();                                 // Tell the next player to vote
                    }
                } _CatchResume ( Election &election ) {                     // Caught after all players vote
                    umpire = election.player;
                    std::cout << " : umpire " << umpire->getId() << std::endl;
                }
            }

            partner[1]->partner[0] = partner[0];                            // Update players to skip this player
            partner[0]->partner[1] = partner[1];                            // Update players to skip this player

            _Resume Terminate ( *this ) _At *umpire;                        // Send terminate instruction to umpire
            umpire->terminate();                                            // Resume umpire
        } catch ( Terminate &terminate ) {
            std::cout << "TERMINATED " << terminate.victim.getId();
            delete &terminate.victim;                                       // Delete the terminated player

            potato.reset();                                                 // Reset the potato
            std::cout << "U ";

        } catch ( Election &election ) {
            std::cout << " -> " << id ;

            /*
             *  The below object compares the player Id to the largest id seen so far in the election
             *      if the current Id is greater than we will replace the current player in the election
             *      with it otherwise we will just propagate the exception with the current highest id player
             */
            if ( election.player->getId() < id ) { _Resume Election ( this ) _At *partner[1]; }
            else { _Resume Election ( election ) _At *partner[1]; }

            partner[1]->vote();                                              // Get the next player to vote
        }

    }

}