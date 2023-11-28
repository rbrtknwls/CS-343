#ifndef CS_343_PRINTER_H
#define CS_343_PRINTER_H


_Monitor Printer {
    struct PrinterState {
        char mainState;
        unsigned int value1, value2, lid;
    };


    const unsigned int NUMBEROFOTHERACTORS = 6;
    const unsigned int PARENTID = 0;
    const unsigned int GROPOFFID = 1;
    const unsigned int WATOFFID = 2;
    const unsigned int NAMESID = 3;
    const unsigned int TRUCKID = 4;
    const unsigned int PLANTID = 5;

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
