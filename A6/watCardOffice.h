#ifndef CS_343_WATCARDOFFICE_H
#define CS_343_WATCARDOFFICE_H

#include <vector>
#include <queue>
#include <uPRNG.h>

#include "watCard.h"
#include "bank.h"
#include "printer.h"

extern PRNG mainPRNG;

_Task WATCardOffice {
    Printer *printer;
    Bank *bank;
    unsigned int numCouriers;

    struct Job {
        unsigned int studentID, amount;
        WATCard * card;
        WATCard::FWATCard result;
        Job( unsigned int studentID, unsigned int amount, WATCard *ca );
        ~Job();
    };

    _Task Courier {
        void main();
        unsigned int localID;
        WATCardOffice* watCardOffice;
        Printer *printer;
      public:
        Courier( unsigned int localID, WATCardOffice *watCardOffice, Printer *printer );
        ~Courier();
    };

    std::queue< Job* > workToDo;
    std::vector< Courier* > courierPool;
    void main();

    bool workDone = false;
  public:
    _Event Lost {};
    WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers );
    WATCard::FWATCard create( unsigned int sid, unsigned int amount ) __attribute__(( warn_unused_result ));
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard * card ) __attribute__(( warn_unused_result ));
    Job * requestWork() __attribute__(( warn_unused_result ));
    ~WATCardOffice();
};

#endif
