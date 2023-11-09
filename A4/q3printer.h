#ifndef CS_343_Q3PRINTER_H
#define CS_343_Q3PRINTER_H

#include "q3tallyVotes.h"
#include "q3voter.h"

/*
 * Below is the header for the printer class, this class will be used by any of the other classes whenever they want
 *   to output values to the screen. This will also handle printing the voter titles and the end of voting.
 */

_Monitor Printer {
    struct PrinterState {                                    // Custom struct to store all possible states
        Voter::States mainState;
        TallyVotes::Tour tour;
        TallyVotes::Ballot vote;
        unsigned int numBlocked, group;
    };

    unsigned int voters;                                     // List of voters
    PrinterState *printBuffer;                               // Array of all possible states for each voter
    bool *hasBeenWrittenTo;                                  // Boolean array for if each voter has been written to

    void flushBuffer();                                      // Method to empty out the buffer
  public:
    Printer( unsigned int voters );
    void print( unsigned int id, Voter::States state );
    void print( unsigned int id, Voter::States state, TallyVotes::Tour tour );
    void print( unsigned int id, Voter::States state, TallyVotes::Ballot vote );
    void print( unsigned int id, Voter::States state, unsigned int numBlocked );
    void print( unsigned int id, Voter::States state, unsigned int numBlocked, unsigned int group );
    ~Printer();
};

#endif //CS_343_Q3PRINTER_H
