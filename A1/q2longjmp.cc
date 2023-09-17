#include <iostream>
#include <csetjmp>
#include <cstdlib>										// access: rand, srand
#include <cstring>										// access: strcmp
using namespace std;
#include <unistd.h>										// access: getpid

#ifdef NOOUTPUT
#define PRINT( stmt )
#else
#define PRINT( stmt ) stmt
#endif // NOOUTPUT

struct E {};											// exception type
intmax_t eperiod = 100, excepts = 0, calls = 0, dtors = 0, depth = 0; // counters
PRINT( struct T { ~T() { dtors += 1; } }; )

long int Ackermann( long int m, long int n, long int depth, jmp_buf* prev_jump_buffer ) {
	calls += 1;

	if ( m == 0 ) {

		if ( rand() % eperiod <= 2 ) {
            PRINT( T t; ) excepts += 1;
            longjmp(*prev_jump_buffer, -1);
        }
		return n + 1;

	} else if ( n == 0 ) {

        jmp_buf new_jump_buffer;
        if (setjmp(new_jump_buffer) == -1) {

            PRINT( cout << " depth " << depth << " E1 " << m << " " << n << " |" );
            if ( rand() % eperiod <= 3 ) {
                PRINT( T t; ) excepts += 1;
                longjmp(*prev_jump_buffer, -1);
            }

        } else {
            return Ackermann( m - 1, 1, depth + 1, &new_jump_buffer );
        }

		PRINT( cout << " E1X " << m << " " << n << endl );

	} else {

        jmp_buf new_jump_buffer;
        if (setjmp(new_jump_buffer) == -1) {

            PRINT( cout << " depth " << depth << " E2 " << m << " " << n << " |" );
            if ( rand() % eperiod == 0 ) {
                PRINT( T t; ) excepts += 1;
                longjmp(*prev_jump_buffer, -1);
            }

        } else {
            Ackermann( m - 1, Ackermann( m, n - 1, depth + 1, &new_jump_buffer ), depth + 1, &new_jump_buffer );
        }

		PRINT( cout << " E2X " << m << " " << n << endl );
	}

	return 0;											// recover by returning 0
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
	volatile intmax_t m = 4, n = 6, seed = getpid();	// default values (volatile needed for longjmp)
	struct cmd_error {};

	try {												// process command-line arguments
		switch ( argc ) {
		  case 5: if ( strcmp( argv[4], "d" ) != 0 ) {	// default ?
			eperiod = convert( argv[4] ); if ( eperiod <= 0 ) throw cmd_error(); }
		  case 4: if ( strcmp( argv[3], "d" ) != 0 ) {	// default ?
			seed = convert( argv[3] ); if ( seed <= 0 ) throw cmd_error(); }
		  case 3: if ( strcmp( argv[2], "d" ) != 0 ) {	// default ?
			n = convert( argv[2] ); if ( n < 0 ) throw cmd_error(); }
		  case 2: if ( strcmp( argv[1], "d" ) != 0 ) {	// default ?
			m = convert( argv[1] ); if ( m < 0 ) throw cmd_error(); }
		  case 1: break;								// use all defaults
		  default: throw cmd_error();
		} // switch
	} catch( ... ) {
		cerr << "Usage: " << argv[0] << " [ m (>= 0) | d [ n (>= 0) | d"
			" [ seed (> 0) | d [ eperiod (> 0) | d ] ] ] ]" << endl;
		exit( EXIT_FAILURE );
	} // try

	srand( seed );

    jmp_buf jump_buffer;
    PRINT( cout << "Arguments " << m << " " << n << " " << seed << " " << eperiod << endl );
    if (setjmp(jump_buffer) == -1) {
        PRINT( cout << "E3" << endl );
    } else {
        long int val = Ackermann( m, n, 0, &jump_buffer );
        PRINT( cout << "Ackermann " << val << endl );
    }

	cout << "calls " << calls << " exceptions " << excepts << " destructors " << dtors << endl;

}
