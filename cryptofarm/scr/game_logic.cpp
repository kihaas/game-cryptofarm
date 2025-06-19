#include "../include/game_logic.h"
#include "../include/textures.h"
#include <iostream>

// Глобальные игровые переменные
std::vector<std::vector<Plant>> beds;
int currentBedCount = 1;

// Константы
constexpr int MAX_BEDS = 5;
constexpr int PLANTS_PER_BED = 6;
constexpr float BED_PRICE = 500.0f;
constexpr float SEED_PRICE = 100.0f;
constexpr float WATER_COST = 10.0f;
constexpr float FERTILIZER_COST = 50.0f;

// Инициализация игры
void initGame() {
    beds.clear();
    beds.resize(MAX_BEDS);
    Plant initialPlant = {0.0f, false, false, 0};
    beds[0].resize(PLANTS_PER_BED, initialPlant);
    currentBedCount = 1;
}

// Добавление новой грядки
bool addNewBed() {
    if (currentBedCount >= MAX_BEDS) return false;
    if (!canAfford(BED_PRICE)) return false;

    spendMoney(BED_PRICE);
    Plant initialPlant = {0.0f, false, false, 0};
    beds[currentBedCount].resize(PLANTS_PER_BED, initialPlant);
    currentBedCount++;
    return true;
}

// Отрисовка игровых объектов
void renderGame(sf::RenderWindow& window) {
    const float bedWidth = 3.0f;
    const float bedHeight = 3.0f;
    const float startX = 480.0f;
    const float startY = 100.0f;
    const float bedSpacing = 300.0f;
    const float plantXOffset = 20.0f;
    const float plantYOffset = -25.0f;
    const float plantSpacing = 40.0f;

    // Отрисовка грядок
    for (int i = 0; i < currentBedCount; ++i) {
        sf::Sprite bedSprite(bedTexture);
        bedSprite.setScale(bedWidth, bedHeight);
        bedSprite.setPosition(startX + i * bedSpacing, startY);


        window.draw(bedSprite);

        // Отрисовка растений
        for (int j = 0; j < beds[i].size(); ++j) {
            if (beds[i][j].growth > 0.0f) {
                sf::Sprite plantSprite;

                if (beds[i][j].growth < 0.33f) {
                    plantSprite.setTexture(plant1Texture);
                }
                else if (beds[i][j].growth < 0.66f) {
                    plantSprite.setTexture(plant2Texture);
                }
                else {
                    plantSprite.setTexture(plant3Texture);
                }

                float scale = 0.1f + beds[i][j].growth * 0.2f;
                plantSprite.setScale(scale, scale);

                float plantX = startX + i * bedSpacing + plantXOffset + j * plantSpacing;
                float plantY = startY + plantYOffset - (plantSprite.getGlobalBounds().height * beds[i][j].growth);

                plantSprite.setPosition(plantX, plantY);
                window.draw(plantSprite);
            }
        }
    }
}

void updateGame(float deltaTime) {
    // Обновляем состояние всех растений
    for (auto& bed : beds) {
        for (auto& plant : bed) {
            if (plant.growth > 0.0f && plant.growth < 1.0f) {
                // Базовая скорость роста
                float growthRate = 0.1f * deltaTime;

                // Модификаторы роста
                if (plant.isWatered) growthRate *= 2.0f;
                if (plant.hasFertilizer) growthRate *= 1.5f;

                plant.growth += growthRate;

                // Определяем стадию роста
                if (plant.growth < 0.33f) {
                    plant.growthStage = 0;
                }
                else if (plant.growth < 0.66f) {
                    plant.growthStage = 1;
                }
                else {
                    plant.growthStage = 2;
                }

                // Сбрасываем флаги после обработки
                plant.isWatered = false;
            }
        }
    }

    // Обновляем экономику
    static float timeSinceLastUpdate = 0.0f;
    timeSinceLastUpdate += deltaTime;

    // Обновляем курс каждые 5 секунд
    if (timeSinceLastUpdate >= 5.0f) {
        updateFarmCoinRate();
        timeSinceLastUpdate = 0.0f;
    }
}