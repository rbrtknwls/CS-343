#include "watCardOffice.h"

// ================== Private Member(s) ==================== //

using namespace std;

void WATCardOffice::Courier::main() {


    for ( ;; ) {
        try {
            _Enable {}
        } catch ( ... ) { break; }
        WATCardOffice::Job* job = watCardOffice->requestWork();
    }

}

void WATCardOffice::main() {

    for ( ;; ) {
        _Accept ( WATCardOffice::create ) {
            unsigned int id = workToDo.back()->studentID;
            unsigned int amount = workToDo.back()->studentID;
            printer->print( Printer::WATCardOffice, 'C', id, amount );

        } or _Accept ( WATCardOffice::transfer ) {
            unsigned int id = workToDo.back()->studentID;
            unsigned int amount = workToDo.back()->studentID;
            printer->print( Printer::WATCardOffice, 'T', id, amount );

        } or _Accept ( WATCardOffice::~WATCardOffice ) {
            break;
        } or _When( !workToDo.empty() ) _Accept ( WATCardOffice::requestWork ) {
            workToDo.pop();
        }
    }

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
    Job* jobToDo = workToDo.front();
    return jobToDo;
}

// ================== Constructor / Destructor ==================== //

WATCardOffice::WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers ) :
    printer( &prt ), bank( &bank ), numCouriers( numCouriers ) {

    printer->print( Printer::WATCardOffice, 'S' );
    for ( unsigned int courierID = 0 ; courierID < numCouriers ; courierID++ ) {

        printer->print( Printer::Courier, courierID, 'S' );
        courierPool.push_back( new Courier( courierID, this ) );
    }
}

WATCardOffice::~WATCardOffice() {

    while ( !workToDo.empty() ) { _Accept ( WATCardOffice::requestWork ) }

    for ( unsigned int courierID = 0 ; courierID < numCouriers ; courierID++ ) {
        _Throw StopWork() _At courierPool[courierID];

        delete courierPool[courierID];
        printer->print( Printer::Courier, courierID, 'F' );
    }
    courierPool.clear();

    printer->print( Printer::WATCardOffice, 'F' );
}


WATCardOffice::Job::Job( unsigned int studentID, unsigned int amount, WATCard *card, Printer *printer  ) :
    studentID( studentID ), amount( amount ), card ( card ), printer( printer ) {}

WATCardOffice::Job::~Job() { printer->print( Printer::WATCardOffice, 'W' ); }

WATCardOffice::Courier::Courier( unsigned int localID, WATCardOffice *watCardOffice ) :
    localID( localID ), watCardOffice( watCardOffice ) {}

WATCardOffice::Courier::~Courier() {

}