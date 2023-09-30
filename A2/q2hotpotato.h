t a#ifndef CS_343_Q2_H
#define CS_343_Q2_H

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

#endif //CS_343_Q2_H
