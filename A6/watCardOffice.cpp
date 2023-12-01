#include "watCardOffice.h"

// ================== Private Member(s) ==================== //

using namespace std;

void WATCardOffice::Courier::main() {

    for ( ;; ) {

        WATCardOffice::Job * job = watCardOffice->requestWork();
      if ( job == nullptr ) { break; }
        //printer->print( Printer::Courier, localID, 't', job->studentID, job->amount );

        watCardOffice->bank->withdraw( job->studentID, job->amount );

        if ( prng(6) == 0 ) {
            printer->print( Printer::Courier, localID, 'L', job->studentID );
        } else {
        //    printer->print( Printer::Courier, localID, 'T', job->studentID, job->amount );
        }

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
            printer->print( Printer::WATCardOffice, 'W' );
        }
    }

}

// ================== Public Member(s) ==================== //

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    Job* job = new Job( sid, amount, new WATCard() );
    workToDo.push( job );
    return job->result;
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard * card ) {
    Job* job = new Job( sid, amount, card );
    workToDo.push( job );
    return job->result;
}

WATCardOffice::Job* WATCardOffice::requestWork() {

  if ( workDone ) { return nullptr; }

    Job* jobToDo = workToDo.front();
    return jobToDo;
}

// ================== Constructor / Destructor ==================== //

WATCardOffice::WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers ) :
    printer( &prt ), bank( &bank ), numCouriers( numCouriers ) {

    printer->print( Printer::WATCardOffice, 'S' );
    for ( unsigned int courierID = 0 ; courierID < numCouriers ; courierID++ ) {
        courierPool.push_back( new Courier( courierID, this, printer ) );
    }
}

WATCardOffice::~WATCardOffice() {
    while ( !workToDo.empty() ) { _Accept ( WATCardOffice::requestWork ) }
    workDone = true;

    for ( unsigned int courierID = 0 ; courierID < numCouriers ; courierID++ ) {
        _Accept ( WATCardOffice::requestWork ) {}
        delete courierPool[courierID];
    }
    courierPool.clear();

    printer->print( Printer::WATCardOffice, 'F' );
}


WATCardOffice::Job::Job( unsigned int studentID, unsigned int amount, WATCard *card ) :
    studentID( studentID ), amount( amount ), card ( card ) {}

WATCardOffice::Job::~Job() {}

WATCardOffice::Courier::Courier( unsigned int localID, WATCardOffice *watCardOffice, Printer *printer ) :
    localID( localID ), watCardOffice( watCardOffice ), printer( printer ) {
    printer->print( Printer::Courier, localID, 'S' );
}

WATCardOffice::Courier::~Courier() {
    printer->print( Printer::Courier, localID, 'F' );
}