#include "q3printer.h"
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

            switch ( currentState ) {
                case Voter::Vote:
                    cout << " " << printBuffer[i].vote.picture << "," << printBuffer[i].vote.statue;
                    cout << "," << printBuffer[i].vote.giftshop;
                    nonSpaceValues += 6;
                    break;

                case Voter::Block:
                    cout << " " << printBuffer[i].numBlocked;
                    nonSpaceValues += 2;
                    break;

                case Voter::Unblock:
                    cout << " " << printBuffer[i].numBlocked;
                    nonSpaceValues += 2;
                    break;

                case Voter::Barging:
                    String toPrint = " " + to_string(printBuffer[i].numBlocked) + " " + to_string(printBuffer[i].group);
                    cout << toPrint;
                    nonSpaceValues += 4
                    break;

                case Voter::Complete:
                    cout << " " << printBuffer[i].tour.tourkind;
                    nonSpaceValues += 2;
                    break;

                case Voter::Going:
                    cout << " " << printBuffer[i].tour.tourkind << " " << printBuffer[i].tour.groupno;
                    nonSpaceValues += 4;
                    break;
                default:
                    break;
            }
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
