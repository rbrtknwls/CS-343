#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <uPRNG.h>

#include "q2potato.h"
#include "q2player.h"

using namespace std;

int main( int argc, char * argv[] ) {

    struct cmd_error {};

    // set the defaults for the program, these will only be updated if a valid replacement is given
    intmax_t seed = getpid();
    PRNG mainPRNG(seed);
    int gamesToPlay = 5;

    try {
        switch( argc ) {
            case (4):
                if (*argv[3] != 'd') {
                    seed = stoi(argv[3]);                                          // update the seed if not given 'd'
                    mainPRNG.set_seed(seed);
                }
            case (3): case (2):
                if (*argv[1] != 'd') { gamesToPlay = stoi(argv[1]); }              // update games if not given 'd'
            case (1):
                break;
            default:
                throw cmd_error();
        } // switch
    } catch (...) {
        cerr << "Usage: " << argv[0]
             << "  [ games | ’d’ [ players | ’d’ [ seed | ’d’ ] ] ] " << endl;
        exit(EXIT_FAILURE);                                                        // TERMINATE
    } // try



    for ( ; gamesToPlay > 0 ; gamesToPlay-- ) {                                    // Loop through games

        /*
         * The number of players in the game might change every game, so we regenerate them each time. We will update
         *  them with random values always, and then replace them if we are given an alternative
         */
        int numberOfPlayers = mainPRNG(2, 10);
        if (argc > 2 && *argv[2] != 'd') { numberOfPlayers = stoi(argv[2]); }

        vector < Player * > players;                                               // stores all player points*
        cout << numberOfPlayers << " players in the game" << endl;

        PRNG playerPRNG(seed);                                                     // create PRNG for player(s)
        PRNG potatoPRNG(seed);                                                     // create PRNG for potato
        Potato potato(potatoPRNG);                                                 // create potato with prng


        /*
         * This loops through all the number of players and initializes the player pointer.
         *  Since each player relies on another player (see the partner field in q2player.h) we need to have multiple
         *  steps to initialize, as we need references to the other players which might not have been created yet.
         */
        for (int id = 0; id < numberOfPlayers; id++) {
            players.push_back(new Player(playerPRNG, id, potato));
        } // for

        Player::umpire = players[0];                                               // set the umpire for the game

        // The below code is for swapping a random index with the umpire as per the requirements of the game
        int swappedPlayer = mainPRNG(1, numberOfPlayers - 1);
        Player * temp = players[swappedPlayer];
        players[swappedPlayer] = players[0];
        players[0] = temp;

        /*
         * Initializes each of the players with the players that are directly beside them, note that we have two
         *  special cases which happens at the first index (index 0) and the last index (index numberOfPlayers-1) this
         *  is because one of the neighbors needs to "loop around" as the first element is neighbours
         *  with the last and vise versa.
         */
        for (int id = 0; id < numberOfPlayers; id++) {
            if (id == 0) {
                players[0]->init(*players[numberOfPlayers - 1], *players[1]);
            } else if (id == numberOfPlayers - 1) {
                players[numberOfPlayers - 1]->init(*players[numberOfPlayers - 2], *players[0]);
            } else {
                players[id]->init(*players[id - 1], *players[id + 1]);
            }
        } // for

        std::cout << "U ";                                                           // game starts with umpire
        players[swappedPlayer]->toss();                                              // toss the potato to umpire


        delete Player::umpire;                                                       // delete last player
        players.clear();                                                             // clear the player list

        if ( gamesToPlay != 1 ) { cout << endl << endl }                             // separate games by spaces
    }

    return 0;


} // main