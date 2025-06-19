#ifndef ECONOMY_H
#define ECONOMY_H

#include <string>

// Глобальные экономические переменные
extern float playerBalance;
extern float farmCoinRate;

// Основные экономические функции
void initEconomy();                          // Инициализация экономики
void updateFarmCoinRate();                   // Обновление курса FarmCoin
float getFarmCoinRate();                     // Получение текущего курса
float getPlayerBalance();                    // Получение баланса игрока
bool canAfford(float amount);                // Проверка возможности покупки
void spendMoney(float amount);               // Списание денег
void addMoney(float amount);                 // Добавление денег
void sellHarvest(float amount);              // Продажа урожая по текущему курсу

#endif