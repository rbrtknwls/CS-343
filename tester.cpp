#include "string"


int main ( int argc, char * argv[] ) {
    std::string file1 = std::string("./") + argv[1];

    system(file1.c_str());
}
