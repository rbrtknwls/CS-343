#include "string"


int main ( int argc, char * argv[] ) {
    std::string file1 = argv[1];
    system("./".c_str() + file1.c_str());
}
