/*
Joseph Calise
ID#: 2380565
calise@chapman.edu
CPSC-350 Section 03
PA2: Not So Super Mario Bros.

Rory Sullivan
ID#: 2401103
rosullivan@chapman.edu
CPSC-350 Section 03
PA2 Not So Super Mario Bros.
*/
#include "Enviorment.h"
#include <iostream>
#include <string>

//if not commandline args provided, it will look for input.txt and will produce output.txt
//order of args is inputfile first then output file.
int main(int argc, char** argv){
    if (argc == 1){
        Enviorment env = Enviorment("input.txt", "output.txt");
        env.runSimulation();
    }else{
        std::string inputFile = argv[1];
        std::string outputFile = argv[2];
        Enviorment env = Enviorment(inputFile, outputFile);
        env.runSimulation();
    }
    return 0;
    
}