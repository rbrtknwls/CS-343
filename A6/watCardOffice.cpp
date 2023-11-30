#include "watCardOffice.h"

// ================== Private Member(s) ==================== //

// ================== Public Member(s) ==================== //

WATCard::FWATCard WATCardOffice::create( unsigned int sid, unsigned int amount ) {
    return
}

WATCard::FWATCard WATCardOffice::transfer( unsigned int sid, unsigned int amount, WATCard * card ) {

}

Job * WATCardOffice::requestWork() {

}

// ================== Constructor / Destructor ==================== //

WATCardOffice::WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers ) :
    printer( &prt ), bank( &bank ), numCouriers( numCouriers ) {
    
    for ( int courier ; courier < numCouriers ; courier++ ) {
        CourierPool.append( new Courier( courier ) );
    }
}