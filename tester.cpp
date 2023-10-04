#include "string"


int main ( int argc, char * argv[] ) {

    for ( int i = 0; i < 5; i++ ) {
        for (int x = 0; x < 5; x++ ) {
            for (int z = 0; z < 5; z++ ) {
                std::string arguments = " "
                if ( i == 0 ) { arguments += "d "}
                else { arguments += std::to_string(i) + " " }

                if ( x == 0 ) { arguments += "d "}
                else { arguments += std::to_string(x) + " " }

                if ( z == 0 ) { arguments += "d "}
                else { arguments += std::to_string(z) + " "}

                std::string arguments +=  " > temp.a 2> temp.a";
                std::string file1 = std::string("./") + argv[1] + arguments;

                system(file1.c_str());
            }
        }
    }

}
