#include "nameserver.h"
#include "printer.h"
#include "vendingmachine.h"

using namespace std;


// ================== Private Method(s) ==================== //

/*
 * Main method for name server, it will accept getting and setting machines to students.
 * It will keep running until it receives a call to its destructor.
 */
void NameServer::main() {

    for ( ;; ) {                                      // Loop until it sees its destructor

        _Accept( ~NameServer ) {                      // Accept the destructor for nameserver
            break;
        } or _When( numMachines == numVendingMachines ) _Accept(getMachine) {
            printer->print(Printer::Kind::NameServer, 'N', currStudentIdx, currMachineIdx);
            machineAssignments[currStudentIdx] = ( currMachineIdx + 1 ) % numVendingMachines;
        } or _When( numMachines == numVendingMachines ) _Accept( getMachineList ) {

        } or _When( numMachines < numVendingMachines ) _Accept( VMregister ) {
            printer->print(Printer::Kind::NameServer, 'R', currMachineIdx);
            numMachines++;                            // Update the number of machines
        } // _Accept

    }
} // NameServer::main


// ================== Public Member(s) ==================== //

// Method for registering a vending machine
void NameServer::VMregister( VendingMachine * vendingmachine ) {
    currMachineIdx = vendingmachine->getId();
    machines[currMachineIdx] = vendingmachine;
} // NameServer::VMregister

// Method a student uses to get a machine
VendingMachine * NameServer::getMachine( unsigned int id ) {
    currStudentIdx = id;
    currMachineIdx = machineAssignments[id];
    return machines[machineAssignments[id]];
} // NameServer::getMachine

// Method you can use to get a list of machines
VendingMachine ** NameServer::getMachineList() {
    return machines;
} // NameServer::getMachineList


// ================== Constructor / Destructor ==================== //


NameServer::NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents ) :
    printer(&prt), numVendingMachines(numVendingMachines), numStudents(numStudents), numMachines(0) {

    printer->print(Printer::Kind::NameServer, 'S');

    machines = new VendingMachine*[numVendingMachines];         // Create a list of vending machines
    machineAssignments = new unsigned int[numStudents];         // Create a relationship between students and machine

    for (unsigned int i = 0; i < numStudents; i++) {
        machineAssignments[i] = i % numVendingMachines;
    } // for

} // NameServer::NameServer

NameServer::~NameServer() {
    delete[] machines;
    delete[] machineAssignments;

    printer->print(Printer::Kind::NameServer, 'F');
} // NameServer::~NameServer