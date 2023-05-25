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
#include "Levels.h"
#include <iostream>

Levels::Levels(){
    char ***gameLevels;
    char **gameboard;
}

Levels::~Levels(){
}

/*
createAllLevels will take advantage of the createGameBoard function.
This will loop through the specified amount of levels and create each leveling using the createGameBoard().
This will return a char*** for easy storage in the enviorment.
*/
char*** Levels::createAllLevels(int levels, int dimensions){
    gameLevels = new char**[levels];
    for (int i = 0; i < levels; i++){
        gameLevels[i] = Levels::createGameBoard(dimensions);
    }
    return gameLevels;
}

/*
createGameBoard() will intake the dimensions for the game.
It will then create a gameboard for the correct dimensions.
It will set all postiions to x meaning nothing.
It will return a char** that will hold the grid for the NxN level.
*/
char** Levels::createGameBoard(int dimensions){
    gameboard = new char* [dimensions];
    for (int i = 0; i < dimensions; i++){
        gameboard[i] = new char[dimensions];
    }
    for (int i = 0; i < dimensions; i++){
        for (int j = 0; j < dimensions; j++){
            gameboard[i][j] = 'x';
        }
    }
    return gameboard;
}
