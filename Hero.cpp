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
#include "Hero.h"
#include<iostream>
#include <cstdlib>
#include <ctime>

/*
Hero takes in 4 parameters, position on the x axis,
position on the y-axis, the dimensions of the gameboard
and the amount of levels to play.
moveHero is a function that controls the movement of
the hero.
interact takes in 1 parameter of a c to determine 
what the hero runs into on the gameboard.
addPositionToFile takes in 1 parameter, levelPlay where
it records the movements of the hero throught the level
and writes to the output file to record the positions 
of the hero on the gameboard throughout the level. 
heroInfo takes in 2 parameters, interaction which 
records what the hero runs into on the gameboard,
and move which records the movements of the hero on
the gameboard.
*/

/***************
Constructors
****************/
Hero::Hero(){
}

Hero::Hero(int lives, int heroPositionX, int heroPositionY, int dimensions, int numLevels){
    int currentLevel = 0;
    this->dimensions = dimensions;
    this->heroPositionX = heroPositionX;
    this->heroPositionY = heroPositionY;
    this->numLevels = numLevels;
    int coins = 0;
    this->lives = lives;
    int powerLevel = 0;
    int enemiesDefeated = 0;
    bool winner = false;
    bool defeatedBoss = false;
}

Hero::~Hero(){

}

/***************
    Methods
****************/

/*******
moveHero()
This will move the hero, but it will also check if the hero is on the edge.
If the hero is on an edge, they will appear on the oposite side from where they
"went off the edge."
moveHero() returns a string that will be used to write to the output file.
********/ 
std::string Hero::moveHero(){
    //interaction needs to be called before we move to see what it is
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);
    //end of not mine.
    int randomRoll = rand() % 100;
    if (randomRoll <= 24){
        //move up
        if (this->heroPositionY == 0){
            this->heroPositionY = (this-> dimensions -1);
        }else{
            this->heroPositionY--;
        };
        return "Mario will move UP.";
    }else if (randomRoll >= 25 && randomRoll < 50){
        //move down
        if (this->heroPositionY == (this->dimensions - 1)){
            this->heroPositionY = 0;
        }else{
            this->heroPositionY++;
        };
        return "Mario will move DOWN.";
    }else if (randomRoll >= 50 && randomRoll < 75){
        //move right
        if (this->heroPositionX == (this->dimensions - 1)){
            this->heroPositionX = 0;
        }else{
            this->heroPositionX++;
        };
        return "Mario will move RIGHT.";
    }else if (randomRoll >= 75 && randomRoll < 100){
        //move left
        if (this->heroPositionX == 0){
            this->heroPositionX = (this-> dimensions -1);
        }else{
            this->heroPositionX--;
        };
        return "Mario will move LEFT.";
    }


}       

/*
interaction() is the method that will be passed a tile that the hero will currently be on.
interaction() will return a string that will be used to write to the output file.
Could be the following.
m: mushroom, increases hero powerlevel by 1
c: will increase the hero's coins by 1
x: nothing, the hero will move on.
g: Goomba, a fight where the hero has an 80% chance to win.
k: Koopa, a fight where the hero has a 60% chance to win.
w: will automatically send the hero to the next level
b: boss, hero has a 50/50 shot at winning. Hero will stay until out of lives or wins.
Boss will win the game if it is the last level, or send the hero to the next level if there are more.
*/
std::string Hero::interaction(char c){
    this->defeatedBoss = false;
    /* BEGIN CODE (reference) FROM SOURCE: https://stackoverflow.com/questions/20201141/same-random-numbers-generated-every-time-in-c */
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    srand((time_t)ts.tv_nsec);
    /* END CODE (reference) FROM SOURCE: https://stackoverflow.com/questions/20201141/same-random-numbers-generated-every-time-in-c */ 
    int randomRoll = rand() % 100;
    if (c == 'c'){
        if (this->coins == 19){
            this->coins = 0;
            this->lives++;
            return "Mario collected a coin and has gained another life!.";
        }else{
            this->coins++;
            return "Mario collected a coin.";
        };
    }else if (c == 'm'){
        if (this->powerLevel < 3){
            this->powerLevel++;
        }
        return "Mario ate a mushroom.";
    }else if (c == 'x'){
        return "Mario visited an empty space.";
    }else if (c == 'g'){
        if (randomRoll >= 80){
            if (this->enemiesDefeated == 6){
                this->enemiesDefeated = 0;
                this->lives++; 
            }
            return "Mario encountered a Goomba, and WON.";
        }else{
            if (this->powerLevel > 0){
                this->powerLevel--;
            }else{
                this->lives--;
            }
            this->enemiesDefeated = 0;
            return "Mario encountered a Goomba, and LOST.";
        };
    }else if (c == 'k'){
        if (randomRoll >= 65){
            if (this->enemiesDefeated == 6){
                this->enemiesDefeated = 0;
                this->lives++; 
            }
            return "Mario encountered a Koopa, and WON.";
        }else{
            if (this->powerLevel > 0){
                this->powerLevel--;
            }else{
                this->lives--;
            }
            this->enemiesDefeated = 0;
            return "Mario encountered a Koopa, and LOST.";
        };
    }else if (c == 'w'){
        this->currentLevel++;
        return "Mario has found a warp pipe.";
    }else if (c == 'b'){
        if (randomRoll >= 50){
            if (this->currentLevel == (this->numLevels-1)){
                this->winner = true;
                this->defeatedBoss = true;
                return "Mario encountered the BOSS, and WON the GAME!!";
            }else{
                this->defeatedBoss = true;
                this->currentLevel++;
                return "Mario encountered the BOSS, and WON!";
            }
        }else{
            if (this->powerLevel >= 2){
                this->powerLevel -= 2;
            }else{
                this->lives--;
            }
            return "Mario encountered the BOSS, and LOST.";
        };
    };
};

/*
addPosition to file is a writer method that will send the heros current level and position to the writer file for the output.
This will return a string that includes the heros position (y,x) and what level they are on.
*/
std::string Hero::addPositionToFile(int levelPlayed){
    std::string info = "======\n";
    info+= "Level: ";
    info+= std::to_string(levelPlayed);
    info+= " Mario is at position: (";
    info+= std::to_string(this->heroPositionY);
    info+= ",";
    info+= std::to_string(this->heroPositionX);
    info+= "). ";

    return info;
}

/*
heroInformation will complete the rest of the output string needed for each move. 
This will return a string that will include:
The interation, Hero powerlevel, hero lives, hero coins, and hero's next movement.
*/
std::string Hero::heroInformation(std::string interaction, std::string movement){
    std::string info = "";
    //print the position to the txt before the move takes place.
    info+= interaction;
    info+= " Mario is at power level ";
    info+= std::to_string(this->powerLevel);
    info+= ". Mario has ";
    info+= std::to_string(this->lives);
    info+= " lives left. Mario has ";
    info+= std::to_string(this->coins);
    info+= " coins. ";
    info+= movement;
    info+= "\n======";

    return info;

}





