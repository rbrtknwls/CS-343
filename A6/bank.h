#ifndef CS_343_BANK_H
#define CS_343_BANK_H


_Monitor Bank {
    unsigned int *studentBalances;
  public:
    Bank( unsigned int numStudents );
    void deposit( unsigned int id, unsigned int amount );
    void withdraw( unsigned int id, unsigned int amount );
    ~Bank();
};


#endif
