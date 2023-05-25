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
#ifndef LEVELS_H
#define LEVELS_H


class Levels{
    public:
    //https://stackoverflow.com/questions/36689025/creating-double-pointer
    char **gameboard;
    char ***gameLevels;
    Levels();
    ~Levels();
    char*** createAllLevels(int levels, int dimensions);
    char** createGameBoard(int dimensions);

};


#endif