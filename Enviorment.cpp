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
#include "Reader.h"
#include "Levels.h"
#include "Hero.h"
#include "Writer.h"
#include <string>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <sstream>


/*
Default constructor is called when no file input / output is specified.
Will default to input.txt and output.txt.
*/
Enviorment::Enviorment(){
    //populated levels:
    //first dim of arr is each level stored
    //second and third equate to the rows and columns.
    std::string inputFile = "input.txt";
    std::string outputFile = "output.txt";
    char ***populatedLevels;
    int currentLevel = 0;
    int numLevels;
    int dimensions;
    int totalTilesPerLevel;
    int startingLives;
    int percentCoins;
    int percentNothing;
    int percentGoomba;
    int percentKoopa;
    int percentMushroom;
}

Enviorment::Enviorment(std::string inputFile, std::string outputFile){
    //populated levels:
    //first dim of arr is each level stored
    //second and third equate to the rows and columns.
    this->inputFile = inputFile;
    this->outputFile =outputFile;
    char ***populatedLevels;
    int currentLevel = 0;
    int numLevels;
    int dimensions;
    int totalTilesPerLevel;
    int startingLives;
    int percentCoins;
    int percentNothing;
    int percentGoomba;
    int percentKoopa;
    int percentMushroom;
}

Enviorment::~Enviorment(){
}


/**************
Part 1:
runSimulator() is a method that will place out hero into the world we have created.
This will be done by choosing two random X, Y coords and creating out hero.
This method will create an instance of our hero pointer and construct him with the proper lives etc.
It will also write the results of our hero placement to a file as well as the level the hero is on.

Part 2:
runSimulator() will then run a while loop that will continue to run while the hero has lives and they havent won the game.

The method has no outputs since the content will be written to a file using the writer class.
***************/

void Enviorment::runSimulation(){
    //PART 1 of the runSimulator()
    Enviorment::setEnviormentVariables(this->inputFile);
    Enviorment::createEnviorment();
    int randomX = rand() % this->dimensions;
    int randomY = rand() % this->dimensions;
    Hero *hero = new Hero(this->startingLives, randomX, randomY, this->dimensions, this->numLevels);
    Writer writer;
    char currentTile = this->populatedLevels[hero->currentLevel][randomY][randomX]; //Store tile's contents to pass into interation.
    //hacky way to add variables to a string to output to writer.
    std::string contentToAdd = "======\nMario will be placed at (";
    contentToAdd+= std::to_string(randomY);
    contentToAdd+= ",";
    contentToAdd+= std::to_string(randomX);
    contentToAdd+= ").\n======";
    writer.addLineToFile(this->outputFile, contentToAdd);
    this->populatedLevels[hero->currentLevel][randomY][randomX] = 'H';
    std::string levelDisplay = "";
    for (int i = 0; i < this->dimensions; i++){ //begin of writing out the current level.
        for (int j = 0; j < this->dimensions; j++){
            levelDisplay += this->populatedLevels[hero->currentLevel][i][j];
        }
        levelDisplay += "\n";
    }
    writer.addLineToFile(this->outputFile, levelDisplay);
    std::string interaction = hero->interaction(currentTile);
    this->populatedLevels[hero->currentLevel][hero->heroPositionY][hero->heroPositionX] = 'x'; //changes the H tile to an x.
    //The below conditionals will determine actions for a W pipe.
    if (currentTile == 'w'){
        writer.addLineToFileNoEnter(this->outputFile, hero->addPositionToFile(hero->currentLevel));
        writer.addLineToFile(this->outputFile, hero->heroInformation(interaction, "Mario will warp."));
    }else{
        writer.addLineToFileNoEnter(this->outputFile, hero->addPositionToFile(hero->currentLevel));
        std::string movement = hero->moveHero();
        writer.addLineToFile(this->outputFile, hero->heroInformation(interaction, movement));
    }

    //Begin of PART 2 of runSimulation()
    while (hero->lives > 0 && hero->winner == false){
        char currentTile = this->populatedLevels[hero->currentLevel][hero->heroPositionY][hero->heroPositionX];
        this->populatedLevels[hero->currentLevel][hero->heroPositionY][hero->heroPositionX] = 'H';
        std::string levelDisplay = "";
        for (int i = 0; i < this->dimensions; i++){
            for (int j = 0; j < this->dimensions; j++){
                levelDisplay += this->populatedLevels[hero->currentLevel][i][j];
            }
            levelDisplay += "\n";
        }
        writer.addLineToFile(this->outputFile, levelDisplay);

        std::string interaction = hero->interaction(currentTile);
        //The below conditionals will determine actions for a W pipe.
            if (currentTile == 'w'){
                writer.addLineToFileNoEnter(this->outputFile, hero->addPositionToFile(hero->currentLevel-1));
                writer.addLineToFile(this->outputFile, hero->heroInformation(interaction, "Mario will warp."));
            }else if (currentTile == 'b'){ //The below conditionals will determine actions for a Boss.
            //The below while loop will have the hero continuing the fight against a boss until they win or are out of lives.
                while (hero->lives >= 1 && hero->defeatedBoss == false){//maybe 
                    std::string interactionHold= hero->interaction('b');
                    //writer.addLineToFile(this->outputFile, levelDisplay);
                    writer.addLineToFileNoEnter(this->outputFile, hero->addPositionToFile(hero->currentLevel));
                    writer.addLineToFile(this->outputFile, hero->heroInformation(interaction, "Mario will stay and try again."));
                    hero->lives--;
                }
                //This conditional will check whether this is the end of the game or if the hero is moving on to the next level after boss fight.
                if (hero->defeatedBoss == true && (hero->currentLevel) == (this->numLevels - 1)){
                    writer.addLineToFileNoEnter(this->outputFile, hero->addPositionToFile(hero->currentLevel));
                    writer.addLineToFile(this->outputFile, hero->heroInformation("Mario BEAT the boss and WON the game.", "Mario will stay celebrate his WIN."));
                }else if (hero->defeatedBoss == true && hero->lives >= 0){
                    std::string movement = hero->moveHero();
                    writer.addLineToFileNoEnter(this->outputFile, hero->addPositionToFile(hero->currentLevel));
                    writer.addLineToFile(this->outputFile, hero->heroInformation("Mario BEAT the boss and will move to the next level.", movement));
                }else{
                    writer.addLineToFileNoEnter(this->outputFile, hero->addPositionToFile(hero->currentLevel));
                    writer.addLineToFile(this->outputFile, hero->heroInformation("Mario fought the BOSS and LOST, he is too tired to try again.", "Mario will stay put and rest."));
                }
            }
            else{
                this->populatedLevels[hero->currentLevel][hero->heroPositionY][hero->heroPositionX] = 'x';
                writer.addLineToFileNoEnter(this->outputFile, hero->addPositionToFile(hero->currentLevel));
                std::string movement = hero->moveHero();
                writer.addLineToFile(this->outputFile, hero->heroInformation(interaction, movement));
            }
    }
    if (hero->winner == true){
        writer.addLineToFile(this->outputFile, "Mario has defeated the boss and won the game!");
    }else{
        writer.addLineToFile(this->outputFile, "Mario has lost all his lives and can not continue!");
    }
    delete hero;
}


/*
setEnviormentVariables will intake a string of a file name
This function will then create a reader and read those lines into the
member variables to make and execute the enviorment our hero will be in.
This method will not return anything, it is used to set the variables for the proper game to be played.
*/
void Enviorment::setEnviormentVariables(std::string inputFile){
    std::string* importedParams;
    Reader read;
    importedParams = read.importFile(inputFile);
    this->numLevels = std::stoi(importedParams[0]);
    this->dimensions = std::stoi(importedParams[1]);
    this->startingLives = std::stoi(importedParams[2]);
    this->percentCoins = std::stoi(importedParams[3]);
    this->percentNothing = std::stoi(importedParams[4]);
    this->percentGoomba = std::stoi(importedParams[5]);
    this->percentKoopa = std::stoi(importedParams[6]);
    this->percentMushroom = std::stoi(importedParams[7]);
    this->totalTilesPerLevel = (this->dimensions * this->dimensions);
    delete[] importedParams;
}

/*
createEnviorment will use the populateboard function to place all of the objects.
After all of the objects are populated, create enviorment 
This method returns nothing. It will simply adjust the gameboard with the correct objects.
*/
void Enviorment::createEnviorment(){
    Levels levels;
    Writer writer;
    populatedLevels = levels.createAllLevels(this->numLevels, this->dimensions);
    Enviorment::populateBoard(this->percentGoomba, 'g');
    Enviorment::populateBoard(this->percentCoins, 'c');
    Enviorment::populateBoard(this->percentKoopa, 'k');
    Enviorment::populateBoard(this->percentMushroom, 'm');
    Enviorment::placeSingleObjects('b');
    Enviorment::placeSingleObjects('w');
    for (int i = 0; i < this->numLevels; i++){
        for (int j = 0; j < this->dimensions; j++){
            std::string line = "";
            for (int k = 0; k < this->dimensions; k++){
                line += this->populatedLevels[i][j][k];
            }
            writer.addLineToFile(this->outputFile, line);
        }
        writer.addLineToFile(this->outputFile, "======");
    }

}

/*
populateBoard will take in a % of how many of the objects there should be as well as the object.
populateBoard will input these objects into the game world for the all of the levels.
This method will return nothing since it is changing the member variable holding the gameboard.
*/
void Enviorment::populateBoard(int percentOfObjects, char objectToPlace){
    //this for-loop is to iterate over every level to populate the board.
    for (int i = 0; i < this->numLevels; i++){
        int objectsLeft = (this->totalTilesPerLevel * (float(percentOfObjects)/100));
        //Within the for-loop, this while loop will populate the correct number
        //of specified objects for the level.
        while (objectsLeft >  0){
            /* using nano-seconds instead of seconds */
            /* BEGIN CODE (reference) FROM SOURCE: https://stackoverflow.com/questions/20201141/same-random-numbers-generated-every-time-in-c */
            struct timespec ts;
            clock_gettime(CLOCK_MONOTONIC, &ts);
            srand((time_t)ts.tv_nsec);
            /* END CODE (reference) FROM SOURCE: https://stackoverflow.com/questions/20201141/same-random-numbers-generated-every-time-in-c */ 
            //randomX,Y will get random coordinates to populate a spot with a character
            int randomX = rand() % this->dimensions;
            int randomY = rand() % this->dimensions;
            //the board is populated with x so it will only change the item
            //if it is x and not another object placed.
            if (this->populatedLevels[i][randomY][randomX] == 'x'){
                this->populatedLevels[i][randomY][randomX] = objectToPlace;
                objectsLeft--;
            }
        }
    }
}

/*
placeSingleObject() intakes a char, and will place those objects on the board.
This function is made for placing the warp pipe and the boss.
this function will not replace a nothing tile. only other objects.
This method will return nothing since it will be adjusting the member variable holding the gameboard.
*/
void Enviorment::placeSingleObjects(char c){
    for (int i = 0; i < this->numLevels; i++){
        if (c == 'w' && i == this->numLevels-1){
            continue;
        }else{
            /* BEGIN CODE (reference) FROM SOURCE: https://stackoverflow.com/questions/20201141/same-random-numbers-generated-every-time-in-c */
            struct timespec ts;
            clock_gettime(CLOCK_MONOTONIC, &ts);
            srand((time_t)ts.tv_nsec);
            /* END CODE (reference) FROM SOURCE: https://stackoverflow.com/questions/20201141/same-random-numbers-generated-every-time-in-c */ 
            //randomX,Y will get random coordinates to populate a spot with a character
            int randomX = rand() % this->dimensions;
            int randomY = rand() % this->dimensions;
            this->populatedLevels[i][randomX][randomY] = c;
        }
    }
}



