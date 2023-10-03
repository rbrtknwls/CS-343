#include "string"


int main ( int argc, char * argv[] ) {
    std::string file1 = argv[1];

    system(std::string("./") + std::string(argv[1]));
}
