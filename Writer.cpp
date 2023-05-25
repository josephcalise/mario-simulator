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
#include "Writer.h"
#include <iostream>
#include <fstream>
#include <string>



Writer::Writer(){

}

Writer::~Writer(){
    
}

/*
addLineToFile will intake a two strings, one being the output file it is going to write to 
and then the following content that should be added to the output file.
This will be used to record the information of the game to the selected output file.
*/
void Writer::addLineToFile(std::string outputFile, std::string contentToAdd){
    std::fstream writingToFile;
    writingToFile.open(outputFile, std::fstream::app);
    if (writingToFile.is_open()){
        writingToFile << contentToAdd<< "\n";
    }
    writingToFile.close();
}

/*
addLineToFileNoEnter will intake a two strings, one being the output file it is going to write to 
and then the following content that should be added to the output file.
This will be used to record the information of the game to the selected output file.
The difference for this than the addLineToFile, is it will not input a \n.
This is used to record the postition and level of the hero before the movement is made.
*/
void Writer::addLineToFileNoEnter(std::string outputFile, std::string contentToAdd){
    std::fstream writingToFile;
    writingToFile.open(outputFile, std::fstream::app);
    if (writingToFile.is_open()){
        writingToFile << contentToAdd;
    }
    writingToFile.close();
}

