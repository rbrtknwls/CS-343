#include "string"


int main ( int argc, char * argv[] ) {

    for ( int i = 0; i < 2; i++ ) {
        for (int x = 0; x < 2; x++ ) {
            for (int z = 0; z < 2; z++ ) {
                std::string arguments = std::to_string(i) + " " + std::to_string(x) + " " + std::to_string(z) + " > temp.a";
                std::string file1 = std::string("./") + argv[1] + arguments;

                system(file1.c_str());
            }
        }
    }

}
