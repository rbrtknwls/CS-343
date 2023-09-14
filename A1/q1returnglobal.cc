#include <iostream>
#include <cstdlib>										// access: rand, srand
#include <cstring>										// access: strcmp
using namespace std;
#include <unistd.h>										// access: getpid

bool flag1 = false;
bool flag2 = false;
bool flag3 = false;

intmax_t eperiod = 10000;								// exception period
int randcnt = 0;

int Rand() { randcnt += 1; return rand(); }

double rtn1( double i ) {
    if ( Rand() % eperiod == 0 ) { flag1 = true; return 0; }
	return i + Rand();
}
double rtn2( double i ) {
    if ( Rand() % eperiod == 0 ) { flag2 = true; return 0; }
    double rtnresult1 = rtn1(i);
    if ( flag1 ) {

        return 0;
    } else {
        return rtnresult1 + Rand();
    }
}
double rtn3( double i ) {
    if ( Rand() % eperiod == 0 ) { flag3 = true; return 0; }
    double rtnresult2 = rtn2(i);
    if ( flag1 || flag2 ) {
        return 0;
    } else {
        return rtnresult2 + Rand();
    }
}

static intmax_t convert( const char * str ) {			// convert C string to integer
    char * endptr;
    errno = 0;											// reset
    intmax_t val = strtoll( str, &endptr, 10 );			// attempt conversion
    if ( errno == ERANGE ) throw std::out_of_range("");
    if ( endptr == str ||								// conversion failed, no characters generated
         *endptr != '\0' ) throw std::invalid_argument(""); // not at end of str ?
    return val;
}

int main( int argc, char * argv[] ) {
	intmax_t times = 100000000, seed = getpid();		// default values
	struct cmd_error {};
	try {
		switch ( argc ) {
		  case 4: if ( strcmp( argv[3], "d" ) != 0 ) {	// default ?
			seed = convert( argv[3] ); if ( seed <= 0 ) throw cmd_error(); }
		  case 3: if ( strcmp( argv[2], "d" ) != 0 ) {	// default ?
			eperiod = convert( argv[2] ); if ( eperiod <= 0 ) throw cmd_error(); }
		  case 2: if ( strcmp( argv[1], "d" ) != 0 ) {	// default ?
			times = convert( argv[1] ); if ( times <= 0 ) throw cmd_error(); }
		  case 1: break;								// use all defaults
		  default: throw cmd_error();
		} // switch
	} catch( ... ) {
		cerr << "Usage: " << argv[0] << " [ times > 0 | d [ eperiod > 0 | d [ seed > 0 | d ] ] ]" << endl;
		exit( EXIT_FAILURE );
	} // try
	srand( seed );

	double rv = 0.0;
	int ev1 = 0, ev2 = 0, ev3 = 0;
	int rc = 0, ec1 = 0, ec2 = 0, ec3 = 0;

	for ( int i = 0; i < times; i += 1 ) {
        flag1 = false;                                  // Reset Flag1
        flag2 = false;                                  // Reset Flag2
        flag3 = false;                                  // Reset Flag3

		rv += rtn3( i );

        if ( flag1 ) {
            ev1 += (short int) Rand(); ec1 += 1;                   // Increase ev1 if flag1 raised
        }
        else if ( flag2 ) {
            ev2 += (int) Rand(); ec2 += 1;                         // Increase ev2 if flag2 raised
        }
        else if ( flag3 ) {
            ev3 += (long int) Rand(); ec3 += 1;                    // Increase ev3 if flag3 raised
        } else {
            rc += 1;
        }

	} // for
	cout << "randcnt " << randcnt << endl;
	cout << "normal result " << rv << " exception results " << ev1 << ' ' << ev2 << ' ' << ev3 << endl;
	cout << "calls "  << rc << " exceptions " << ec1 << ' ' << ec2 << ' ' << ec3 << endl;
}
