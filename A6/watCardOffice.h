#ifndef CS_343_WATCARDOFFICE_H
#define CS_343_WATCARDOFFICE_H

#include <vector>

#include "watCard.h"
#include "bank.h"
#include "printer.h"

_Task WATCardOffice {
    struct Job {
        unsigned int studentID;
        WATCard::FWATCard result;
        Job( unsigned int studentID ) : studentID( studentID ) {}
    };

    _Task Courier {
        void main();
        unsigned int localID;
      public:
        Courier( localID );
    };
    void main();

    Printer *printer;
    Bank *bank;
    unsigned int numCouriers;

    Vector<Courier*> CourierPool;
  public:
    _Event Lost {};
    WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers );
    WATCard::FWATCard create( unsigned int sid, unsigned int amount ) __attribute__(( warn_unused_result ));
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard * card ) __attribute__(( warn_unused_result ));
    Job * requestWork() __attribute__(( warn_unused_result ));
};

#endif
