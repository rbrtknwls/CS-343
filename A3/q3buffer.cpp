//
// Created by robde on 2023/10/23.
//

#include "q3buffer.h"

#include <iostream>

using namespace std;

int main( int argc, char * argv[] ) {
    int cons = 5;
    int prods = 3;
    int produce = 10;
    int buffersize = 10;
    int delays = numberOfProducers + numberOfConsumers
    int processors = 1;

    struct cmd_error {
    };

    try {

        switch (argc) {
            case 7:
                if ( *argv[6] != 'd' ) { processors = stoi(argv[6]) }
            case 6:
                if ( *argv[5] != 'd' ) { delays = stoi(argv[5]); }
            case 5:
                if ( *argv[4] != 'd' ) { buffersize = stoi(argv[4]); }
            case 4:
                if ( *argv[3] != 'd' ) { produce = stoi(argv[3]); }
            case 3:
                if ( *argv[2] != 'd' ) { prods = stoi(argv[2]); }
                if ( argc == 6 && *argv[5] != 'd' ) {
                    delays = numberOfProducers + numberOfConsumers
                }
            case 2:
                if ( *argv[1] != 'd' ) { cons = stoi(argv[1]); }
                break;
            default:                                       // wrong number of options
                throw cmd_error();
        } // switch

    } catch (...) {                                        // catch any
        cerr << "Usage: " << argv[0]
             << " [ cons | ’d’ [ prods | ’d’ [ produce | ’d’ [ buffersize | ’d’ [ delay | ’d’ "
             << "[ processors | ’d’ ] ] ] ] ] ] " << endl;
        exit(EXIT_FAILURE);                                // TERMINATE
    } // try

    cout << cons << endl;
    cout << prods << endl;
    cout << produce << endl;
    cout << buffersize << endl;
    cout << delays << endl;
    cout << processors << endl;



}