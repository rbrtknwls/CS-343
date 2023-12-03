#include "student.h"

Student::Student( Printer & prt, WATCardOffice & cardOffice, Groupoff & groupoff,
    unsigned int id, unsigned int maxPurchases ) : printer( &prt ), watCardOffice ( &cardOffice ),
    groupoff( &groupoff ), localID( id ) {

    numberOfPurchases = prng( maxPurchases ) + 1;
    favouriteFlavour = prng( 4 );

}
