#include "string"


int main ( int argc, char * argv[] ) {

    for ( int i = 0; i < 5; i++ ) {
        for (int x = 0; x < 5; x++ ) {
            for (int z = 2; z < 5; z++ ) {
                std::string arguments = " ";
                if ( i == 0 ) { arguments += "d "; }
                else { arguments += std::to_string(i) + " "; }

                if ( x == 0 ) { arguments += "d "; }
                else { arguments += std::to_string(x) + " "; }

                if ( z == -1 ) { arguments += "d "; }
                else { arguments += std::to_string(z) + " "; }

                std::string arg1 = arguments + " > temp.a 2> temp.a";
                std::string arg2 = arguments + " > temp.b 2> temp.b";

                std::string file1 = std::string("./") + argv[1] + arg1;
                std::string file2 = std::string("./") + argv[2] + arg2;

                system(file1.c_str());
                system(file2.c_str());

                system("diff temp.a temp.b");
            }
        }
    }

}
