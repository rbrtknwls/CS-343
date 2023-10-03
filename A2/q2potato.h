#ifndef CS_343_POTATO_H
#define CS_343_POTATO_H


class Potato {
    PRNG & prng;                                                // Stores random number generator to use
    int currentTicks;                                           // Stores current ticks left
  public:
    _Event Explode {};
    Potato( PRNG & prng, unsigned int maxTicks = 10 );
    void reset( unsigned int maxTicks = 10 );                    // Reset number of ticks
    void countdown();                                            // Decrease number of ticks
};


#endif //CS_343_POTATO_H
