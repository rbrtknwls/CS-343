#ifndef CS_343_PRINTER_H
#define CS_343_PRINTER_H


_Monitor Printer {

    struct PrinterState {
        char mainState;
        unsigned int value1, value2, lid, numTerms;
    };

    enum IDS { PARENT = 0, GROUPOFF = 1, WATOFF = 2, NAMES = 3, TRUCK = 4, PLANT = 5 };

    const unsigned int NUMBEROFSTATICACTORS = 6;

    unsigned int numStudents;
    unsigned int numVendingMachines;
    unsigned int numCouriers;
    unsigned int totalNumberOfActors;

    PrinterState *printBuffer;
    bool *hasBeenWrittenTo;

    void flushBuffer();
  public:

    enum Kind { Parent, Groupoff, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    void print( Kind kind, char state );
    void print( Kind kind, char state, unsigned int value1 );
    void print( Kind kind, char state, unsigned int value1, unsigned int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, unsigned int value1 );
    void print( Kind kind, unsigned int lid, char state, unsigned int value1, unsigned int value2 );
    ~Printer();

  private:
    int kindToID( Kind kind );
};


#endif
