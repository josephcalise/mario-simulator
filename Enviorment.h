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
#ifndef EVIORMENT_H
#define ENVIORMENT_H
#include <string>

class Enviorment{
    public:
    std::string inputFile;
    std::string outputFile;
    char ***populatedLevels;
    int currentLevel;
    int numLevels;
    int dimensions;
    int totalTilesPerLevel;
    int startingLives;
    int percentCoins;
    int percentNothing;
    int percentGoomba;
    int percentKoopa;
    int percentMushroom;
    Enviorment();
    Enviorment(std::string inputFile, std::string outputFile);
    ~Enviorment();
    //hero information 
    void runSimulation();
    void setEnviormentVariables(std::string inputFile);
    void createEnviorment();
    void populateBoard(int percentOfObjects, char objectToPlace);
    void placeSingleObjects(char c);
    
};


#endif