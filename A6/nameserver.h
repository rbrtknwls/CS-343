#ifndef NAMESERVER_H
#define NAMESERVER_H

// Forward Declarations
_Task VendingMachine;
_Monitor Printer;


_Task NameServer {
	void main();
    Printer * printer;
    unsigned int numVendingMachines;
    unsigned int numStudents;
    unsigned int numMachines;
    VendingMachine **machines;
    unsigned int *machineAssignments;
    unsigned int currMachineIdx;
    unsigned int currStudentIdx;
  public:
	NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents );
	void VMregister( VendingMachine * vendingmachine );
	VendingMachine * getMachine( unsigned int id ) __attribute__(( warn_unused_result ));
	VendingMachine ** getMachineList() __attribute__(( warn_unused_result ));
  ~NameServer();
};


#endif