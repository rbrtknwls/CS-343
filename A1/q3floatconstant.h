#ifndef __FLOC_H__
#define __FLOC_H__ 1

_Coroutine FloatConstant {
	char ch;											// character passed by cocaller
    bool isFloatPositive;                               // bool for if the float is positive
    int mantissa;                                       // holds the mantissa of the float
    int characteristic;                                 // holds the characteristic of the float
    int exponent;                                       // holds the exponent of the float

    int numberOfDigits;                                 /* stores how many digits have currently been read into
                                                        * the current component of the float, to add a new digit
                                                        * we just do component += (digit)*(10^numdigits)
                                                        */

    void main();

  public:
	enum {
        EOT = '\003',                                   // end of text
        EXL = 'e',                                      // lowercase exponent
        EXU = 'E',                                      // uppercase exponent
        DOT = '.',                                      // separator between points
        FSL = 'f',                                      // lowercase float suffix
        FSU = 'F',                                      // uppercase float suffix
        LSL = 'l',                                      // lowercase long suffix
        LSU = 'L'                                       // uppercase long suffix
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