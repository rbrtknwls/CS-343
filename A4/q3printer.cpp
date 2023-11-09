#include "q3printer.h"
#include <string>
#include <iostream>

using namespace std;

// ================== Private Methods ==================== //
void Printer::flushBuffer () {
    for ( unsigned int i = 0; i < voters; i++ ) {                   // Loop through each voter
        if ( hasBeenWrittenTo[i] ) {                                // if data is current
            int nonSpaceValues = 0;                                 // store spaces used up in print
            Voter::States currentState = printBuffer[i].mainState;
            nonSpaceValues++;                                       // state always take one space

            cout << currentState;
            string toPrint;                                         // store string to print
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
                    cout << " " << printBuffer[i].tour.tourkind;       // Due to weirdness with char, print directly
                    toPrint = " b";                                    // Set to print after the fact
                    break;

                case Voter::Going:
                    cout << " " << printBuffer[i].tour.tourkind;       // Same weirdness with tourkind
                    toPrint = " " + to_string(printBuffer[i].tour.groupno);
                    cout << toPrint;
                    toPrint += " +";                                   // toPrint should include 2 chars already print
                    break;

                default:
                    break;
            }

            nonSpaceValues += toPrint.length();                        // Add length of printed values

            cout << string( 8-nonSpaceValues, ' ' );                   // Print space till we reach 8


        } else {
            cout << "\t";                                              // print 8 spaces
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
        hasBeenWrittenTo[i] = false;                                    // Each users buffer hasnt been written too
        cout << "V" << i;                                               // Print user tags at top

        if ( i != voters-1 ) {
            if ( i < 10 ) { cout << "      "; }
            else { cout << "     "; }
        }
    }

    cout << endl;

    for ( unsigned int i = 0; i < voters; i++ ) {
        cout << "*******";                                             // Print "*" under user
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

    cout << "*****************" << endl;                                         // Printed at the very end
    cout << "All tours ended" << endl;

    // At this point the buffer still has some more values so we will flush it one more time!
    Printer::flushBuffer();

    delete printBuffer;
    delete hasBeenWrittenTo;
}
