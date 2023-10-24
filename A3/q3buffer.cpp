#include "q3buffer.h"

#include <iostream>
#include <vector>

using namespace std;

int main( int argc, char * argv[] ) {
    int cons = 5;                                                         // default for the number of consumers
    int prods = 3;                                                        // default for the number of producers
    int produce = 10;                                                     // number of values the producers create
    int buffersize = 10;                                                  // maximum size of the buffer
    int delays = cons + produce;                                          // default for the delay
    int processors = 1;                                                   // default number of processors

    struct cmd_error { };

    try {

        switch (argc) {
            case 7:
                if ( *argv[6] != 'd' ) { processors = stoi(argv[6]); }    // update processors
            case 6:
                if ( *argv[5] != 'd' ) { delays = stoi(argv[5]); }        // update delays
            case 5:
                if ( *argv[4] != 'd' ) { buffersize = stoi(argv[4]); }    // update the buffersize
            case 4:
                if ( *argv[3] != 'd' ) { produce = stoi(argv[3]); }       // update the number of produce
            case 3:
                if ( *argv[2] != 'd' ) { prods = stoi(argv[2]); }         // update the number of prods
            case 2:
                if ( *argv[1] != 'd' ) { cons = stoi(argv[1]); }          // update the number of cons
                if ( argc < 6 || *argv[5] == 'd' ) {
                    delays = cons + prods;
                }
                break;
            default:                                                      // wrong number of options
                throw cmd_error();
        } // switch

    } catch (...) {                                                       // catch any
        cerr << "Usage: " << argv[0]
             << " [ cons | ’d’ [ prods | ’d’ [ produce | ’d’ [ buffersize | ’d’ [ delay | ’d’ "
             << "[ processors | ’d’ ] ] ] ] ] ] " << endl;
        exit(EXIT_FAILURE);                                               // TERMINATE
    } // try

    uProcessor p[processors - 1] __attribute__(( unused ));

    BoundedBuffer<int> buffer ( buffersize );                             // setup the buffer
    int consumerResults[cons] = {0};                                      // save the results of consumers
    vector<Consumer*> consList;                                           // set up list of consumers
    vector<Producer*> prodList;                                           // set up list of producers

    for (int i = 0 ; i < prods; i++ ) {                                   // add prods number of producers
        prodList.push_back( new Producer( buffer, produce, delays ) );
    }

    for (int i = 0 ; i < cons; i++ ) {                                    // add cons number of consumers
        consList.push_back( new Consumer( buffer, produce, consumerResults[i] ) );
    }

    for (int i = 0 ; i < prods; i++ ) {
        delete prodList[i];                                               // delete each producer
    }

    buffer.poison();                                                      // poison the buffer

    int totalSum = 0;
    for (int i = 0 ; i < cons; i++ ) {
        delete consList[i];                                               // delete each consumer
        totalSum += consumerResults[i];                                   // add up each result
    }

    cout << "total: " << totalSum << endl;
    cout << endl;
    cout << "Total Producer/Consumer blocks in insert/remove " << buffer.blocks() << endl;

}