#include "string"


int main ( int argc, char * argv[] ) {
    std::string file1 = std::str(argv[1]);
    system("./" + file1);
}
