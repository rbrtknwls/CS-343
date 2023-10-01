#include <uPRNG.h>
#include <iostream>

#include "q2potato.h"

Potato::Potato( PRNG &prng, unsigned int maxTicks ) : prng( prng ) {
    currentTicks = prng(1, maxTicks);
}

void Potato::reset(unsigned int maxTicks) {
    currentTicks = prng(1, maxTicks);
}

void Potato::countdown() {
    if (currentTicks-- == 0) {
        throw Explode();
    }
}