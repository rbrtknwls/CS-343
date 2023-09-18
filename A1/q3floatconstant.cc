#include <iostream>
#include "/u/r2knowles/CS-343/A1/q3floatconstant.h"

using namespace std;

_Coroutine FloatConstant {
	char ch;											// character passed by cocaller
	void main() {
        suspend();
        cout << "Silly Billy" << endl;

    }
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
