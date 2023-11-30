#include "watCardOffice.h"

// ================== Private Member(s) ==================== //

using namespace std;

void WATCardOffice::main() {

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
    Job* job = new Job( sid, amount, new WATCard(), printer );
    workToDo.push( job );
    return job->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard * card ) {
    Job* job = new Job( sid, amount, card, printer );
    workToDo.push( job );
    return job->result;
}

WATCardOffice::Job* WATCardOffice::requestWork() {
    while ( workToDo.empty() ) { _Accept ( WATCardOffice::create || WATCardOffice::transfer ); }
    Job* jobToDo = workToDo.front();
    workToDo.pop();
    return jobToDo;
}

// ================== Constructor / Destructor ==================== //

WATCardOffice::WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers ) :
    printer( &prt ), bank( &bank ), numCouriers( numCouriers ) {

    for ( unsigned int courier ; courier < numCouriers ; courier++ ) {
        CourierPool.push_back( new Courier( courier ) );
    }
}


WATCardOffice::Job::Job( unsigned int studentID, unsigned int amount, WATCard *card, Printer *printer  ) :
    studentID( studentID ), amount( amount ), card ( card ), printer( printer ) {}

WATCardOffice::Job::~Job() { printer->print( Printer::WATCardOffice, 'W' ); }

void WATCardOffice::Courier::main() {
    for ( ;; ) {

    }
}

// ================== Constructor / Destructor ==================== //

WATCardOffice::Courier::Courier( unsigned int localID ) : localID( localID ) {}

WATCardOffice::Courier::~Courier() {

}