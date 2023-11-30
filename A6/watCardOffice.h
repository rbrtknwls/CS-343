#ifndef CS_343_WATCARDOFFICE_H
#define CS_343_WATCARDOFFICE_H

#include "watCard.h"

_Task WATCardOffice {
    struct Job {
        Args args;
        WATCard::FWATCard result;
        Job( Args args ) : args( args ) {}
    };
    _Task Courier { ... };
    void main();

  public:
    _Event Lost {};
    WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers );
    WATCard::FWATCard create( unsigned int sid, unsigned int amount ) __attribute__(( warn_unused_result ));
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard * card ) __attribute__(( warn_unused_result ));
    Job * requestWork() __attribute__(( warn_unused_result ));
};

#endif
