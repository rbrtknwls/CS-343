#include "string"
#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <uPRNG.h>

using namespace std;
int main ( int argc, char * argv[] ) {
    srand(getpid());


    for ( int testNum = 0; testNum < 10; testNum++ ) {
        ofstream currentFile;
        currentFile.open("input" + std::to_string(testNum) + ".txt");
        int numberOfTests = rand()%10 + 5;

        for ( int currLength = 0; currLength < numberOfTests; currLength++ ) {
            currentFile << "HIII";

        }

        currentFile.close();


    }




    /* A2 - Q2
    for ( int i = 0; i < 10; i++ ) {
        for (int x = 2; x < 10; x++ ) {
            for (int z = 2; z < 10; z++ ) {
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
    }*/

}
