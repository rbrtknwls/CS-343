#ifndef CS_343_Q3PRINTER_H
#define CS_343_Q3PRINTER_H


_Monitor / _Cormonitor Printer {	// chose one of the two kinds of type constructor
  public:
    Printer( unsigned int voters );
    void print( unsigned int id, Voter::States state );
    void print( unsigned int id, Voter::States state, TallyVotes::Tour tour );
    void print( unsigned int id, Voter::States state, TallyVotes::Ballot vote );
    void print( unsigned int id, Voter::States state, unsigned int numBlocked );
    void print( unsigned int id, Voter::States state, unsigned int numBlocked, unsigned int group );
};


#endif //CS_343_Q3PRINTER_H
