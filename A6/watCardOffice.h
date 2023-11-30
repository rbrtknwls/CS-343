#ifndef CS_343_WATCARDOFFICE_H
#define CS_343_WATCARDOFFICE_H

#include <vector>
#include <queue>

#include "watCard.h"
#include "bank.h"
#include "printer.h"

_Task WATCardOffice {
    /*
    Printer *printer;
    Bank *bank;
    unsigned int numCouriers;

    struct Job {
        unsigned int studentID, amount;
        WATCard * card;

        WATCard::FWATCard result;
        Job( unsigned int studentID, unsigned int amount, WATCard *card  );
        ~Job();
    };
    Queue< Job* > workToDo;
    */
    _Task Courier {
        void main();
        unsigned int localID;
      public:
        Courier( unsigned int localID );
        ~Courier();
    };
    Vector< Courier* > CourierPool;

    void main();

  public:
    _Event Lost {};
    WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers );
    WATCard::FWATCard create( unsigned int sid, unsigned int amount ) __attribute__(( warn_unused_result ));
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard * card ) __attribute__(( warn_unused_result ));
    Job * requestWork() __attribute__(( warn_unused_result ));
};

#endif
