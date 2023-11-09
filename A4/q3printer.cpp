#include "q3printer.h"
#include <string>
#include <iostream>

using namespace std;

// ================== Private Methods ==================== //
void Printer::flushBuffer () {
    for ( unsigned int i = 0; i < voters; i++ ) {
        if ( hasBeenWrittenTo[i] ) {
            int nonSpaceValues = 0;
            Voter::States currentState = printBuffer[i].mainState;
            nonSpaceValues++;

            cout << currentState;
            string toPrint;
            switch ( currentState ) {
                case Voter::Vote:
                    toPrint = " " + to_string(printBuffer[i].vote.picture) + "," +
                                    to_string(printBuffer[i].vote.statue) + "," +
                                    to_string(printBuffer[i].vote.giftshop);
                    cout << toPrint;
                    break;

                case Voter::Block:
                    toPrint = " " + to_string(printBuffer[i].numBlocked);
                    cout << toPrint;
                    break;

                case Voter::Unblock:
                    toPrint = " " + to_string(printBuffer[i].numBlocked);
                    cout << toPrint;
                    break;

                case Voter::Barging:
                    toPrint = " " + to_string(printBuffer[i].numBlocked) + " " + to_string(printBuffer[i].group);
                    cout << toPrint;
                    break;

                case Voter::Complete:
                    toPrint = " " + to_string(printBuffer[i].tour.tourkind);
                    cout << toPrint;
                    break;

                case Voter::Going:
                    toPrint = " "  + to_string(printBuffer[i].tour.tourkind) + " " +
                                     to_string(printBuffer[i].tour.groupno);
                    cout << toPrint;
                    break;
                    
                default:
                    break;
            }
            nonSpaceValues += toPrint.length();

            cout << string( 8-nonSpaceValues, ' ' );


        } else {
            cout << "\t";
        }
    }

    cout << endl;
    for ( unsigned int i = 0; i < voters; i++ ) { hasBeenWrittenTo[i] = false; }
}

// ================== Public Methods ==================== //

Printer::Printer( unsigned int voters ) : voters(voters) {
    hasBeenWrittenTo = new bool[voters];
    printBuffer = new PrinterState[voters];


    for ( unsigned int i = 0; i < voters; i++ ) {
        hasBeenWrittenTo[i] = false;
        cout << "V" << i;

        if ( i != voters-1 ) {
            if ( i < 10 ) { cout << "      "; }
            else { cout << "     "; }
        }
    }

    cout << endl;

    for ( unsigned int i = 0; i < voters; i++ ) {
        cout << "*******";
        if ( i != voters-1 ) { cout << " "; }
    }

    cout << endl;
}

void Printer::print( unsigned int id, Voter::States state ) {
    if ( hasBeenWrittenTo[id] ) { flushBuffer(); }
    printBuffer[id].mainState = state;
    hasBeenWrittenTo[id] = true;
}

void Printer::print( unsigned int id, Voter::States state, TallyVotes::Tour tour ) {
    if ( hasBeenWrittenTo[id] ) { flushBuffer(); }
    printBuffer[id].mainState = state;
    printBuffer[id].tour = tour;
    hasBeenWrittenTo[id] = true;
}

void Printer::print( unsigned int id, Voter::States state, TallyVotes::Ballot vote ) {
    if ( hasBeenWrittenTo[id] ) { flushBuffer(); }
    printBuffer[id].mainState = state;
    printBuffer[id].vote = vote;
    hasBeenWrittenTo[id] = true;
}

void Printer::print( unsigned int id, Voter::States state, unsigned int numBlocked ) {
    if ( hasBeenWrittenTo[id] ) { flushBuffer(); }
    printBuffer[id].mainState = state;
    printBuffer[id].numBlocked = numBlocked;
    hasBeenWrittenTo[id] = true;
}

void Printer::print( unsigned int id, Voter::States state, unsigned int numBlocked, unsigned int group ) {
    if ( hasBeenWrittenTo[id] ) { flushBuffer(); }
    printBuffer[id].mainState = state;
    printBuffer[id].numBlocked = numBlocked;
    printBuffer[id].group = group;
    hasBeenWrittenTo[id] = true;
}

Printer::~Printer() {
    delete printBuffer;
    delete hasBeenWrittenTo;
}
