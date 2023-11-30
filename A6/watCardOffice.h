#ifndef CS_343_WATCARDOFFICE_H
#define CS_343_WATCARDOFFICE_H

#include <vector>
#include <queue>

#include "watCard.h"
#include "bank.h"
#include "printer.h"
#include "courier.h"

_Task WATCardOffice {
    static Printer *printer;
    Bank *bank;
    unsigned int numCouriers;

    struct Job {
        unsigned int studentID, amount;
        WATCard * card;
        WATCard::FWATCard result;
        Job( unsigned int studentID, unsigned int amount, WATCard *card  );
        ~Job();
    };

    std::queue< Job* > workToDo;
    std::vector< Courier* > CourierPool;
    void main();
    static void jobDone() { printer->print(Printer::WATCardOffice, 'W'); };

  public:
    _Event Lost {};
    WATCardOffice( Printer & prt, Bank & bank, unsigned int numCouriers );
    WATCard::FWATCard create( unsigned int sid, unsigned int amount ) __attribute__(( warn_unused_result ));
    WATCard::FWATCard transfer( unsigned int sid, unsigned int amount, WATCard * card ) __attribute__(( warn_unused_result ));
    Job * requestWork() __attribute__(( warn_unused_result ));
};

#endif
