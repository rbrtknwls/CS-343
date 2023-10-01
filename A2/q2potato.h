#ifndef CS_343_POTATO_H
#define CS_343_POTATO_H


class Potato {
    PRNG & prng;
    int currentTicks;
  public:
    _Event Explode {};
    Potato( PRNG & prng, unsigned int maxTicks = 10 ) {};
    void reset( unsigned int maxTicks = 10 ) {};
    void countdown();
};


#endif //CS_343_POTATO_H
