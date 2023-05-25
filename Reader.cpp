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
#include "Reader.h"
#include <iostream>
#include <fstream>
#include <string>

Reader::Reader(){

}

Reader::~Reader(){
    
}

/*
importFile 
Takes in a string of a file name and read the file.
returns a pointer to a string with the contents of the file.
the file will be read in this order: 
    [0] = num of levels
    [1] = dimensions of the grid
    [2] = number of initial lives
    [3] = num of levels
    [4] = % of gridpoints coins
    [5] = % of gridpoints nothing
    [6] = % of gridpoints Goombas
    [7] = % of gridpoints Koopas
    [8] = % of gridpoints mushrooms
*/

/*
importFile will intake a string of a file name and read said file it will intake the input file name as a string.
This will return a string pointer that is an array of input items from the input file.
This will be used in enviorment to set all of the member variables to allow the game to run 
based on the file inputs.
*/
std::string* Reader::importFile(std::string input){
    int lineCounter = 0;
    std::string *fileContent = new std::string[8];
    std::fstream readingFile;
    readingFile.open(input, std::ios::in);
    if (readingFile.is_open()){
        std::string fileLine;
        while (std::getline(readingFile, fileLine)){
            fileContent[lineCounter] = fileLine;
            lineCounter++;
        }
        readingFile.close();
    }
    return fileContent;

}