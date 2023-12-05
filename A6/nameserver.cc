#include "nameserver.h"
#include "printer.h"
#include "vendingmachine.h"

using namespace std;


// ================== Private Method(s) ==================== //


void NameServer::main() {

    for ( ;; ) {

        _Accept( ~NameServer ) {
            break;
        } or _When( numMachines == numVendingMachines ) _Accept(getMachine) {
            printer.print(Printer::Kind::NameServer, 'N', currStudentIdx, currMachineIdx);
            machineAssignments[currStudentIdx] = ( currMachineIdx + 1 ) % numVendingMachines;
        } or _Accept( getMachineList ) {

        } or _When( numMachines < numVendingMachines ) _Accept( VMregister ) {
            printer.print(Printer::Kind::NameServer, 'R', currMachineIdx);
            numMachines++;
        } // _Accept

    }
} // NameServer::main


// ================== Public Member(s) ==================== //


void NameServer::VMregister( VendingMachine * vendingmachine ) {
    currMachineIdx = vendingmachine->getId();
    machines[currMachineIdx] = vendingmachine;
} // NameServer::VMregister

VendingMachine * NameServer::getMachine( unsigned int id ) {
    currStudentIdx = id;
    currMachineIdx = machineAssignments[id];
    return machines[machineAssignments[id]];
} // NameServer::getMachine

VendingMachine ** NameServer::getMachineList() {
    return machines;
} // NameServer::getMachineList


// ================== Constructor / Destructor ==================== //


NameServer::NameServer( Printer & prt, unsigned int numVendingMachines, unsigned int numStudents ) :
printer(prt), numVendingMachines(numVendingMachines), numStudents(numStudents), numMachines(0) {

    printer.print(Printer::Kind::NameServer, 'S');

    machines = new VendingMachine*[numVendingMachines];
    machineAssignments = new unsigned int[numStudents];

    for (unsigned int i = 0; i < numStudents; i++) {
        machineAssignments[i] = i % numVendingMachines;
    } // for

} // NameServer::NameServer

NameServer::~NameServer() {
    delete[] machines;
    delete[] machineAssignments;

    printer.print(Printer::Kind::NameServer, 'F');
} // NameServer::~NameServer