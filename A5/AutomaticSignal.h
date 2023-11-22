#ifndef CS_343_AUTOMATICSIGNAL_H
#define CS_343_AUTOMATICSIGNAL_H

#define AUTOMATIC_SIGNAL uCondition bench;

#define WAITUNTIL( pred, before, after )  \
    if ( !pred ) {                        \
        before;                           \
                                          \
        while ( !pred ) { bench.wait(); } \
                                          \
    }                                     \
    after;

#define EXIT() while ( !bench.empty() ) { bench.signal(); }
#endif
