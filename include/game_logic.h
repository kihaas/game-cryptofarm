#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H


#include <SFML/Graphics.hpp>
#include <vector>
#include "../include/economy.h"

struct GardenBed {
    sf::Vector2f position;
    bool isOccupied = false;
};

struct Plant {
    int growthStage = 0;
    bool isWatered = false;
    bool hasFertilizer = false;
    bool isFertilized;
    sf::Vector2f position;

    Plant() : growthStage(0), isWatered(false), isFertilized(false) {}
};


extern std::vector<std::vector<Plant>> beds;
extern int currentBedCount;


void initGame();
void updateGame(float deltaTime);
void renderGame(sf::RenderWindow& window);
int getBedCount();
bool addNewBed();
bool plantSeed(int bedIndex);
void waterPlant(int bedIndex);
void fertilizePlant(int bedIndex);
float harvestPlant(int bedIndex, int plantIndex);


#endif
