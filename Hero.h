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
#ifndef HERO_H
#define  HERO_H
#include <string>

class Hero{
    public:
    /***************
    Member Variables
    ****************/
    //positionX will define hero's position on the x-axis (in the nested array)
    //positionY will define the hero's position on the y axis (which array)
    //coins
    //lives
    //powerLevel can increase with eating a mushroom.
    //powerLevel will be printed as PL(int) ranging from 0-2
    //enemiesDefeated will count the number of enemies defeated. At 7 Hero gains a new life.
    int dimensions;
    int currentLevel;
    int numLevels;
    int heroPositionX;
    int heroPositionY;
    int coins;
    int lives;
    int powerLevel;
    int enemiesDefeated;
    bool winner;
    bool defeatedBoss;

    /***************
    Methods
    ****************/
    Hero();
    Hero(int lives, int positionX, int positionY, int dimensions, int numLevels);
    ~Hero();
    std::string moveHero();
    std::string interaction(char c);
    std::string addPositionToFile(int levelPlayed);
    std::string heroInformation(std::string interaction, std::string movement);


};

#endif