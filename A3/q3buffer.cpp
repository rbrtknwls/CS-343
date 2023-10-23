#include "q3buffer.h"

#include <iostream>
#include <vector>

using namespace std;

int main( int argc, char * argv[] ) {
    int cons = 5;
    int prods = 3;
    int produce = 10;
    int buffersize = 10;
    int delays = cons + produce;
    int processors = 1;

    struct cmd_error {
    };

    try {

        switch (argc) {
            case 7:
                if ( *argv[6] != 'd' ) { processors = stoi(argv[6]); }
            case 6:
                if ( *argv[5] != 'd' ) { delays = stoi(argv[5]); }
            case 5:
                if ( *argv[4] != 'd' ) { buffersize = stoi(argv[4]); }
            case 4:
                if ( *argv[3] != 'd' ) { produce = stoi(argv[3]); }
            case 3:
                if ( *argv[2] != 'd' ) { prods = stoi(argv[2]); }
            case 2:
                if ( *argv[1] != 'd' ) { cons = stoi(argv[1]); }
                if ( argc < 6 || *argv[5] == 'd' ) {
                    delays = cons + prods;
                }
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


    BoundedBuffer<int> buffer ( buffersize );
    int consumerResults[cons] = {0};
    vector<Consumer*> consList;
    vector<Producer*> prodList;

    for (int i = 0 ; i < prods; i++ ) {
        prodList.push_back( new Producer( buffer, produce, delays ) );
    }
    std::cout << "done";
    for (int i = 0 ; i < cons; i++ ) {
        consList.push_back( new Consumer( buffer, produce, consumerResults[i] ) );
    }
    std::cout << "done";
    buffer.poison();

    for (int i = 0 ; i < prods; i++ ) {
        delete prodList[i];
    }
    int totalSum = 0;
    for (int i = 0 ; i < cons; i++ ) {
        delete consList[i];
        totalSum += consumerResults[i];
    }

    cout << "total: " << totalSum << endl;
    cout << endl;
    cout << "Total Producer/Consumer blocks in insert/remove " << endl;

}