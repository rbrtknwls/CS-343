using namespace std;
_Coroutine FloatConstant {
    char ch;											// character passed by cocaller
    void main();

    public:
    enum { EOT = '\003' };								// end of text
    _Event Match {										// last character match
        public:
        double value;									// floating-point value
        Match( double value ) : value( value ) {}
    };

    _Event Error {};									// last character invalid
    void next( char c );
};
