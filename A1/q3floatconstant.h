#ifndef __FLOC_H__
#define __FLOC_H__ 1

_Coroutine FloatConstant {
	char ch;											// character passed by cocaller
    bool isFloatPositive;                               // bool for if the float is positive
    bool isExponentPositive;                            // bool for if the exponent is positive

    double mantissa;                                    // holds the mantissa of the float
    long characteristic;                                // holds the characteristic of the float
    long exponent;                                      // holds the exponent of the float
    double totalFloat;                                  // holds the summation of our value to return

    int numberOfDigits;                                 /* stores how many digits have currently been read into
                                                        * the current component of the float, to add a new digit
                                                        * we just do component += (digit)*(10^numdigits)
                                                        */

    void main();

  public:
	enum {
        EOT = '\003'                                    // end of text
    };
	_Event Match {										// last character match
	  public:
		double value;									// floating-point value
		Match( double value ) : value( value ) {}
	};

	_Event Error {};									// last character invalid
    void next( char c );
};

#endif