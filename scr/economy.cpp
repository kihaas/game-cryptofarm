#include "../include/economy.h"
#include <iostream>
#include <ctime>
#include <cmath>



float playerBalance = 1500.0f;
float farmCoinRate = 1.0f;


void initEconomy() {
    srand(time(0));
    updateFarmCoinRate();
}


bool canAfford(float amount) {
    return playerBalance >= amount;
}


void spendMoney(float amount) {
    if (canAfford(amount)) {
        playerBalance -= amount;
    }
}


void addMoney(float amount) {
    playerBalance += amount;
}


float getPlayerBalance() {
    return playerBalance;
}


float getFarmCoinRate() {
    return farmCoinRate;
}


void updateFarmCoinRate() {
    float randomChange = (rand() % 200 - 100) / 1000.0f; // -10% to +10%
    farmCoinRate *= (1.0f + randomChange);
    if (farmCoinRate < 0.1f) farmCoinRate = 0.1f;
}
