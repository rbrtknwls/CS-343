#ifndef __FLOC_H__
#define __FLOC_H__ 1

_Coroutine FloatConstant {
	char ch;											// character passed by cocaller
    bool isPositive = true;                             // assume float is positive
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

#endif