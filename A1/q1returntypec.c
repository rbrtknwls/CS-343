#include <stdlib.h>										// access: rand, srand
#include <string.h>										// access: strcmp
#include <unistd.h>										// access: getpid
#include <stdio.h>
#include <stdint.h>
#include <errno.h>

typedef union RtnResult {
    double normalReturn;
    short int rtn1ex;
    int rtn2ex;
    long rtn3ex;
} RtnResult;

intmax_t eperiod = 10000;								// exception period
int randcnt = 0;

int Rand() { randcnt += 1; return rand(); }

RtnResult rtn1( double i ) {

    RtnResult rtnResult;
    rtnResult.rtn1ex = 0;
    rtnResult.rtn2ex = 0;
    rtnResult.rtn3ex = 0;
    rtnResult.normalReturn = 0;

    if ( Rand() % eperiod == 0 ) { rtnResult.rtn1ex = (short int)Rand(); }
    else { rtnResult.normalReturn = i + Rand(); }

	return rtnResult;
}

RtnResult rtn2( double i ) {

    RtnResult rtn1Result = rtn1(i);

    if ( Rand() % eperiod == 0 ) { rtn1Result.rtn2ex = (int)Rand(); }
    else if ( rtn1Result.rtn1ex == 0 ) { rtn1Result.normalReturn = i + Rand(); }

    return rtn1Result;

}

RtnResult rtn3( double i ) {
    RtnResult rtn2Result = rtn2(i);

    if ( Rand() % eperiod == 0 ) { rtn2Result.rtn3ex = (long int)Rand(); }
    else if ( rtn2Result.rtn1ex == 0 && rtn2Result.rtn2ex == 0 ) {
        rtn2Result.normalReturn = i + Rand();
    }

    return rtn2Result;
}

static intmax_t convert( const char * str , void* errorLabel) {            // convert C string to integer
    char *endptr;
    errno = 0;                                            // reset
    intmax_t val = strtoll(str, &endptr, 10);            // attempt conversion
   if (errno == ERANGE) goto *errorLabel;
   if (endptr == str ||                                // conversion failed, no characters generated
        *endptr != '\0')
       goto *errorLabel;
    return val;

}

int main( int argc, char * argv[] ) {
	intmax_t times = 100000000, seed = getpid();		// default values
	struct cmd_error {};

    void* errorLabel = &&ERROR;                     // Store error label

    switch ( argc ) {
      case 4: if ( strcmp( argv[3], "d" ) != 0 ) {	// default ?
        seed = convert( argv[3], errorLabel );
       if ( seed <= 0 ) goto *errorLabel;
          }
      case 3: if ( strcmp( argv[2], "d" ) != 0 ) {	// default ?
        eperiod = convert( argv[2], errorLabel );
       if ( eperiod <= 0 ) goto *errorLabel;
      }
      case 2: if ( strcmp( argv[1], "d" ) != 0 ) {	// default ?
        times = convert( argv[1], errorLabel  );
       if ( times <= 0 ) goto *errorLabel;
      }
      case 1: break; 					          	// use all defaults
      default: goto *errorLabel;
    } // switch

    goto DEFAULT;
    ERROR:
    fprintf(stderr, "Usage: %s [ times > 0 | d [ eperiod > 0 | d [ seed > 0 | d ] ] ]", argv[0]);
    exit( EXIT_FAILURE );

    DEFAULT:

	srand( seed );

	double rv = 0.0;
	int ev1 = 0, ev2 = 0, ev3 = 0;
	int rc = 0, ec1 = 0, ec2 = 0, ec3 = 0;

	for ( int i = 0; i < times; i += 1 ) {
        RtnResult rtn3Result = rtn3( i );
        printf("%d %d %d %ld", rtn3Result.normalReturn, rtn3Result.rtn1ex, rtn3Result.rtn2ex, rtn3Result.rtn3ex);

        if ( rtn3Result.rtn1ex != 0 ) {
            ev1 += rtn3Result.rtn1ex; ec1 += 1;
        } else if ( rtn3Result.rtn2ex != 0 ) {
            ev2 += rtn3Result.rtn2ex; ec2 += 1;
        } else if ( rtn3Result.rtn3ex != 0 ) {
            ev3 += rtn3Result.rtn3ex; ec3 += 1;
        } else {
            rv += rtn3Result.normalReturn; rc += 1;
        }

	} // for
	printf("randcnt %d\n", randcnt);
	printf("normal result %f exception results %d %d %d\n", rv, ev1, ev2, ev3);
	printf("calls %d exceptions %d %d %d\n", rc, ec1, ec2, ec3);
}
