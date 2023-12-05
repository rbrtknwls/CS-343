#ifndef CS_343_STUDENT_H
#define CS_343_STUDENT_H

#include "printer.h"
#include "watCardOffice.h"
#include "groupoff.h"
#include "nameserver.h"
#include "bottlingplant.h"


_Task Student {
    Printer * printer;
    NameServer & nameServer;
    WATCardOffice *watCardOffice;
    Groupoff *groupoffer;
    

    unsigned int localID;
    unsigned int numberOfPurchases;
    BottlingPlant::Flavours flavour;

    WATCard::FWATCard watcard;
    WATCard::FWATCard giftcard;

    void main();

  public:
    Student( Printer & prt, NameServer & nameServer, WATCardOffice & cardOffice, Groupoff & groupoff,
        unsigned int id, unsigned int maxPurchases );
    ~Student();
};

#endif //CS_343_STUDENT_H
