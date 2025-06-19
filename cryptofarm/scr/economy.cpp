#include "../include/economy.h"
#include <iostream>
#include <ctime>
#include <cmath>

// Глобальные переменные
float playerBalance = 1000.0f;
float farmCoinRate = 1.0f;

// Инициализация экономики
void initEconomy() {
    srand(time(0));
    updateFarmCoinRate();
}

// Проверка достаточности средств
bool canAfford(float amount) {
    return playerBalance >= amount;
}

// Списание средств
void spendMoney(float amount) {
    if (canAfford(amount)) {
        playerBalance -= amount;
    }
}

// Добавление средств
void addMoney(float amount) {
    playerBalance += amount;
}

// Получение баланса
float getPlayerBalance() {
    return playerBalance;
}

// Получение курса
float getFarmCoinRate() {
    return farmCoinRate;
}

// Обновление курса (упрощенная версия)
void updateFarmCoinRate() {
    float randomChange = (rand() % 200 - 100) / 1000.0f; // -10% to +10%
    farmCoinRate *= (1.0f + randomChange);
    if (farmCoinRate < 0.1f) farmCoinRate = 0.1f;
}