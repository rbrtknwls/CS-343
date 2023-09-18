#ifndef _FloatConstant_h_
#define _FloatConstant_h_
_Coroutine FloatConstant {
	char ch;											// character passed by cocaller
	void main();										// coroutine main
  public:
	enum { EOT = '\003' };								// end of text
	_Event Match {										// last character match
	  public:
		double value;									// floating-point value
		Match( double value ) : value( value ) {}
	};
	_Event Error {};									// last character invalid

	void next( char c ) {
		ch = c;											// communication input
		resume();										// activate
	}
};

#endif // _FloatConstant_h_
