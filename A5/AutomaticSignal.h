#ifndef CS_343_AUTOMATICSIGNAL_H
#define CS_343_AUTOMATICSIGNAL_H

#define AUTOMATIC_SIGNAL uCondition bench;

#define WAITUNTIL( pred, before, after ) . . .

#define EXIT() while ( !bench.empty() ) { begin.signal(); }
#endif
