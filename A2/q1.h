//
// Created by robde on 2023-09-29.
//

#ifndef CS_343_Q1_H
#define CS_343_Q1_H

template<typename T> _Coroutine Binsertsort {
    T value;
    void main();
    public:
    _Event Sentinel {};
    void sort( T value ) {
        Binsertsort::value = value;
        resume();
    }
    T retrieve() {
        resume();
        return value;
    }
};



#endif //CS_343_Q1_H
