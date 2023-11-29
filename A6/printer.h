#ifndef CS_343_PRINTER_H
#define CS_343_PRINTER_H


_Monitor Printer {

    struct PrinterState {
        char mainState;
        unsigned int value1, value2, lid;
    };

    enum IDS
    {
        PARENT = 0,
        GROPOFF = 1,
        WATOFF = 2,
        NAMES = 3,
        TRUCKID = 4,
        PLANTID = 5
    };

    unsigned int numStudents;
    unsigned int numVendingMachines;
    unsigned int numCouriers;

    PrinterState *printBuffer;
    bool *hasBeenWrittenTo;
  public:

    enum Kind { Parent, Groupoff, WATCardOffice, NameServer, Truck, BottlingPlant, Student, Vending, Courier };
    Printer( unsigned int numStudents, unsigned int numVendingMachines, unsigned int numCouriers );
    void print( Kind kind, char state );
    void print( Kind kind, char state, unsigned int value1 );
    void print( Kind kind, char state, unsigned int value1, unsigned int value2 );
    void print( Kind kind, unsigned int lid, char state );
    void print( Kind kind, unsigned int lid, char state, unsigned int value1 );
    void print( Kind kind, unsigned int lid, char state, unsigned int value1, unsigned int value2 );

};


#endif
