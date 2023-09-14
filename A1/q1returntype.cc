#include <iostream>
#include <cstdlib>										// access: rand, srand
#include <cstring>										// access: strcmp
using namespace std;
#include <unistd.h>										// access: getpid
#include <variant>

intmax_t eperiod = 10000;								// exception period
int randcnt = 0;
int Rand() { randcnt += 1; return rand(); }

variant< double, short int> rtn1( double i ) {
    if ( Rand() % eperiod == 0 ) { return (short int)Rand(); }
	return i + Rand();
}

variant< double, short int, int>  rtn2( double i ) {
    if ( Rand() % eperiod == 0 ) { return (int)Rand(); }
    variant<double, short int> ret1variant = rtn1(i);

    if ( holds_alternative<short int>(ret1variant) ) {
        return get<short int>(ret1variant);
    } else {
        return get<double>(ret1variant) + Rand();
    }
}

variant< double, short int, int, long int>  rtn3( double i ) {
    if ( Rand() % eperiod == 0 ) { return (long int)Rand(); }

    variant< double, short int, int> ret2variant = rtn2(i);

    if ( holds_alternative<short int>(ret2variant) ) {
        return get<short int>(ret2variant);
    } else if (holds_alternative<int>(ret2variant) ){
        return get<int>(ret2variant);
    } else {
        return get<double>(ret2variant) + Rand();
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

        variant< double, short int, int, long int> ret3variant = rtn3( i );

        if ( holds_alternative<short int>(ret3variant) ) {
            ev1 += get<short int>(ret3variant); ec1 += 1;
        } else if ( holds_alternative<int>(ret3variant) ){
            ev2 += get<short int>(ret3variant); ec2 += 1;
        } else if ( holds_alternative<long int>(ret3variant) ){
            ev3 += get<short int>(ret3variant); ec3 += 1;
        } else {
            rv += get<double>(ret3variant); rc += 1;
        }

	} // for
	cout << "randcnt " << randcnt << endl;
	cout << "normal result " << rv << " exception results " << ev1 << ' ' << ev2 << ' ' << ev3 << endl;
	cout << "calls "  << rc << " exceptions " << ec1 << ' ' << ec2 << ' ' << ec3 << endl;
}
