#include "watCardOffice.h"

// ================== Private Member(s) ==================== //


WATCardOffice::main() {

    printer->print( Printer::WATCardOffice, 'S' );

    for ( ;; ) {
        _Accept ( WATCardOffice::create ) {
            unsigned int id = workToDo.back()->studentID;
            unsigned int amount = workToDo.back()->studentID;
            printer->print( Printer::WATCardOffice, 'C', id, amount );

        } or _Accept ( WATCardOffice::transfer ) {
            unsigned int id = workToDo.back()->studentID;
            unsigned int amount = workToDo.back()->studentID;
            printer->print( Printer::WATCardOffice, 'T', id, amount );
        } or _Accept ( WATCardOffice::requestWork ) {}
        _Else { break; }
    }

    while ( !workToDo.empty() ) { _Accept ( WATCardOffice::requestWork ) }

    printer->print( Printer::WATCardOffice, 'F' );

}

// ================== Public Member(s) ==================== //

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    Job job = new Job( sid, amount, WATCard() );
    workToDo.push_back( job );
    return job.result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard * card ) {
    Job job = new Job( sid, amount, card );
    workToDo.push( job );
    return job.result;
}

Job * WATCardOffice::requestWork() { return workToDo.pop(); }

// ================== Constructor / Destructor ==================== //

WATCardOffice::WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers ) :
    printer( &prt ), bank( &bank ), numCouriers( numCouriers ) {

    for ( int courier ; courier < numCouriers ; courier++ ) {
        CourierPool.append( new Courier( courier ) );
    }
}