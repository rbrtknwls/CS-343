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

    intmax_t seed = getpid();
    PRNG mainPRNG(seed);

    int games = 5;
    int numberOfPlayers = mainPRNG(2, 10);

    try {
        if ( argc > 4 ) {
            cerr << "Too many arguments!" << endl;
            throw cmd_error();
        } // if

        if ( argc >= 2 ) {
            if ( *argv[1] != 'd' ) { games = stoi( argv[1] ); }
        } // if

        if ( argc >= 3 ){
            if ( *argv[2] != 'd' ) { numberOfPlayers = stoi( argv[2] ); }
        } // if

        if ( argc == 4 ) {
            if ( *argv[3] != 'd' ) {
                seed = stoi( argv[3] );
                mainPRNG.set_seed( seed );

                if ( *argv[2] == 'd' ) { numberOfPlayers = mainPRNG( 2, 10 ); }
            } // if
        } // if


    } catch (...) {
        cerr << "Usage: " << argv[0]
             << "  [ games | ’d’ [ players | ’d’ [ seed | ’d’ ] ] ] " << endl;
        exit(EXIT_FAILURE);                            // TERMINATE
    } // try


    // Initial set up
    PRNG playerPRNG( seed );
    PRNG potatoPRNG( seed );
    Potato potato( potatoPRNG );

    cout << numberOfPlayers << " players in the game" << endl;

    vector<Player*> players;

    for (int id = 0; id < numberOfPlayers; id++) {
        players.push_back( new Player( playerPRNG, id, potato ) );
    } // for

    Player* umpire = players[0];
    int swappedPlayer = mainPRNG(1,numberOfPlayers-1);

    players[swappedPlayer]->init( *players[1], *players[numberOfPlayers-1] );
    for (int id = 1; id < numberOfPlayers-1; id++) {


        switch ( id ) {
            case 1: {
                Player * nextPlayer = players[2];
                if ( swappedPlayer == 2 ) { nextPlayer = players[0]; }

                players[1]->init( *players[swappedPlayer], *nextPlayer );
                break;
            } // first player
            case numberOfPlayers-1: {
                Player * previousPlayer = players[numberOfPlayers - 2];
                if (swappedPlayer == numberOfPlayers - 2) { previousPlayer = players[0]; }

                players[numberOfPlayers - 1]->init(*previousPlayer, *players[swappedPlayer]);
                break;
            } // last player

            default: {
                cout << "haiiii" << endl;
            } // default

        } // switch
    } // for

    return 0;


} // main