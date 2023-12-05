#include "watCardOffice.h"

using namespace std;

// ================== Private Member(s) ==================== //

/*
 * Main method for Courier, it will look for work and execute it wherever possible.
 * This courier will block on a withdrawal until the amount of money in the account is sufficent.
 */
void WATCardOffice::Courier::main() {

    for ( ;; ) {

        // Get the next job in the queue
        WATCardOffice::Job * job = watCardOffice->requestWork();
      if ( job == nullptr ) { break; }                                // Exit if no work to do
        printer->print( Printer::Courier, localID, 't', job->studentID, job->amount );

        watCardOffice->bank->withdraw( job->studentID, job->amount ); // Get money out of the bank (blocking)
        job->card->deposit( job->amount );                            // Deposit into the watchword

        if ( prng(6) == 0 ) {                                         // 20% of the time we lose the watcard
            printer->print( Printer::Courier, localID, 'L', job->studentID );

            delete job->card;                                         // Delete "lost" card
            job->result.delivery( new WATCardOffice::Lost );          // Send the exception
        } else {
            printer->print( Printer::Courier, localID, 'T', job->studentID, job->amount );
            job->result.delivery( job->card );                        // Send the card to the user
        } // if

        delete job;                                                   // Delete the job (saves future)
    } // for

} // WATCardOffice::Courier::main

/*
 * Main method for the WatCardOffice will schedule work for the couriers to do.
 * The majority of the work in the mutex members has been refactored into main.
 */
void WATCardOffice::main() {

    for ( ;; ) {

        // While we have work to give, accept requestWork
        _When( !workToDo.empty() ) _Accept ( WATCardOffice::requestWork ) {
            printer->print( Printer::WATCardOffice, 'W' );

            workToDo.pop();

        // Always accept work to create a watcard
        } or  _Accept ( WATCardOffice::create ) {
            unsigned int id = workToDo.back()->studentID;
            unsigned int amount = workToDo.back()->amount;
            printer->print( Printer::WATCardOffice, 'C', id, amount );

        // Always accept work to transfer money into watcard
        } or _Accept ( WATCardOffice::transfer ) {
            unsigned int id = workToDo.back()->studentID;
            unsigned int amount = workToDo.back()->amount;
            printer->print( Printer::WATCardOffice, 'T', id, amount );

        // Always accept the destructor for Watcard office
        } or _Accept ( WATCardOffice::~WATCardOffice ) {
            break;
        } // _Accept

    } // for

} // WATCardOffice::main

// ================== Public Member(s) ==================== //

// Mutex member to create a Watcard
WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    Job* job = new Job( sid, amount, new WATCard() );            // Add job to queue
    workToDo.push( job );
    return job->result;
} // WATCardOffice::create

// Mutex member to transfer funds from a Watcard
WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard * card ) {
    Job* job = new Job( sid, amount, card );                     // Add job to queue
    workToDo.push( job );
    return job->result;
} // WATCardOffice::transfer

// Mutex member to request work (called by couriers)
WATCardOffice::Job* WATCardOffice::requestWork() {
  if ( workDone ) { return nullptr; }                           // Return nothing if done (and will exit)

    Job* jobToDo = workToDo.front();
    return jobToDo;
} // WATCardOffice::requestWork

// ================== Constructor / Destructor ==================== //

WATCardOffice::WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers ) :
    printer( &prt ), bank( &bank ), numCouriers( numCouriers ) {

    printer->print( Printer::WATCardOffice, 'S' );

    // Create an array of courier's to do the processing for the watcard office
    for ( unsigned int courierID = 0 ; courierID < numCouriers ; courierID++ ) {
        courierPool.push_back( new Courier( courierID, this, printer ) );
    } // for
} // WATCardOffice::WATCardOffice

WATCardOffice::~WATCardOffice() {
    // Wait for all the remaining requested work to finish (students have exited by now)
    while ( !workToDo.empty() ) { _Accept ( WATCardOffice::requestWork ) }
    workDone = true;                                          // Done work

    for ( unsigned int courierID = 0 ; courierID < numCouriers ; courierID++ ) {
        _Accept ( WATCardOffice::requestWork ) {}             // Break courier out of main
        delete courierPool[courierID];                        // Delete the courier
    } // for
    courierPool.clear();

    printer->print( Printer::WATCardOffice, 'F' );
} // WATCardOffice::~WATCardOffice


WATCardOffice::Job::Job( unsigned int studentID, unsigned int amount, WATCard *card ) :
    studentID( studentID ), amount( amount ), card ( card ) {

} // WATCardOffice::Job::Job

WATCardOffice::Job::~Job() {

} // WATCardOffice::Job::~Job


WATCardOffice::Courier::Courier( unsigned int localID, WATCardOffice *watCardOffice, Printer *printer ) :
    localID( localID ), watCardOffice( watCardOffice ), printer( printer ) {
    printer->print( Printer::Courier, localID, 'S' );
} // WATCardOffice::Courier::Courier

WATCardOffice::Courier::~Courier() {
    printer->print( Printer::Courier, localID, 'F' );
} // WATCardOffice::Courier::~Courier