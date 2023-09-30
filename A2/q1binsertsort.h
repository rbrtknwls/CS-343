//
// Created by robde on 2023-09-29.
//

#ifndef CS_343_Q1_H
#define CS_343_Q1_H

template<typename T> _Coroutine Binsertsort {
    T value;
    T pivot;
    void main();
   public:
    _Event Sentinel {};
    Binsertsort();
    void sort( T value );
    T retrieve();
};



#endif //CS_343_Q1_H
