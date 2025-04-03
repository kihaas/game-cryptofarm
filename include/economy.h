#ifndef ECONOMY_H
#define ECONOMY_H


#include <string>


extern float playerBalance;
extern float farmCoinRate;



void initEconomy();
void updateFarmCoinRate();
float getFarmCoinRate();
float getPlayerBalance();
bool canAfford(float amount);
void spendMoney(float amount);
void addMoney(float amount);
void sellHarvest(float amount);


#endif
