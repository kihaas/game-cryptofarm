#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include <SFML/Graphics.hpp>
#include <vector>
#include "../include/economy.h"

struct Plant {
    float growth;        // Уровень роста (0-1)
    bool isWatered;      // Полито ли растение
    bool hasFertilizer;  // Удобрено ли растение
    int growthStage;     // Текущая стадия роста (0-3)
};

// Глобальные игровые переменные
extern std::vector<std::vector<Plant>> beds;
extern int currentBedCount;

// Основные игровые функции
void initGame();                            // Инициализация игры
void updateGame(float deltaTime);           // Обновление игрового состояния
void renderGame(sf::RenderWindow& window);  // Отрисовка игровых объектов
int getBedCount();                          // Получение количества грядок
bool addNewBed();                           // Добавление новой грядки
bool plantSeed(int bedIndex);               // Посадка семени
void waterPlant(int bedIndex, int plantIndex);  // Полив растения
void fertilizePlant(int bedIndex, int plantIndex); // Удобрение растения
float harvestPlant(int bedIndex, int plantIndex);  // Сбор урожая

#endif