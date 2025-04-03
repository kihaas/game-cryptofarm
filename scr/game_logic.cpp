#include "../include/game_logic.h"
#include "../include/textures.h"
#include "../include/economy.h"
#include "../include/ui.h"
#include <iostream>


std::vector<std::vector<Plant>> beds;
std::vector<GardenBed> gardenBeds;
int currentBedCount = 1;
int currentPlantCount = 1;


constexpr int MAX_BEDS = 8;
constexpr int PLANTS_PER_BED = 2;
constexpr float BED_PRICE = 500.0f;
constexpr float SEED_PRICE = 250.0f;
constexpr float WATER_COST = 100.0f;
constexpr float FERTILIZER_COST = 150.0f;
constexpr float PLANT_OFFSET_X = 60.0f;  // Смещение относительно грядки
constexpr float PLANT_OFFSET_Y = -50.0f;
constexpr float PLANT_SPACING_X = 50.f; // Расстояние между растениями по X
constexpr float PLANT_SPACING_Y = 30.f;
constexpr int MAX_PLANTS_PER_BED = 2;
const float PLANT_SPACING = 80.0f;



sf::Texture wateredBedTexture;
sf::Texture normalBedTexture;



void initGame() {
    beds.clear();
    beds.resize(MAX_BEDS);
    for (auto& bed : beds) {
        bed.resize(PLANTS_PER_BED);
    }
    gardenBeds.clear();
    gardenBeds.resize(MAX_BEDS);

    // Загрузка текстур
    wateredBedTexture.loadFromFile("../assets/sprites/bed_watered.png");
    normalBedTexture.loadFromFile("../assets/sprites/bed.png");
    bedTexture.loadFromFile("../assets/sprites/bed.png");
}

bool plantSeed(int bedIndex) {
    if (bedIndex < 0 || bedIndex >= currentBedCount) {
        std::cerr << "Invalid bed index!" << std::endl;
        return false;
    }

    // Проверка денег перед посадкой
    if (!canAfford(SEED_PRICE)) {
        std::cout << "Недостаточно FarmCoin! Нужно: " << SEED_PRICE
                  << ", есть: " << getPlayerBalance() << std::endl;
        return false;
    }

    // Поиск свободного места на грядке
    for (int plantIdx = 0; plantIdx < PLANTS_PER_BED; ++plantIdx) {
        if (beds[bedIndex][plantIdx].growthStage == 0) { // Если место свободно
            beds[bedIndex][plantIdx].growthStage = 1;    // Сажаем семя (1я стадия)
            spendMoney(SEED_PRICE);
            std::cout << "Семя посажено на грядку " << (bedIndex + 1)
                      << ". Осталось денег: " << getPlayerBalance() << std::endl;

            // Расчет позиции растения
            float plantX = gardenBeds[bedIndex].position.x + (plantIdx * PLANT_SPACING_X);
            float plantY = gardenBeds[bedIndex].position.y - PLANT_SPACING_Y;

            beds[bedIndex][plantIdx].position = sf::Vector2f(plantX, plantY);

            return true;
        }
    }

    std::cerr << "No free space in bed " << bedIndex << "!" << std::endl;
    return false;
}

void waterPlant(int bedIndex) {
    if (bedIndex < 0 || bedIndex >= currentBedCount) return;

    // Проверяем, есть ли растения на выбранной грядке
    bool hasPlants = false;
    for (int plantIndex = 0; plantIndex < PLANTS_PER_BED; ++plantIndex) {
        if (beds[bedIndex][plantIndex].growthStage > 0) {
            hasPlants = true;
            break;
        }
    }

    if (!hasPlants) {
        std::cout << "На грядке " << (bedIndex + 1) << " нет растений для полива!" << std::endl;
        return;
    }

    // Поливаем все растения на выбранной грядке
    for (int plantIndex = 0; plantIndex < PLANTS_PER_BED; ++plantIndex) {
        if (beds[bedIndex][plantIndex].growthStage > 0 && beds[bedIndex][plantIndex].growthStage < 3) {
            if (canAfford(WATER_COST)) {
                spendMoney(WATER_COST);
                beds[bedIndex][plantIndex].growthStage++; // Увеличиваем фазу роста
                std::cout << "Фаза роста растения на грядке " << (bedIndex + 1) << " увеличена!" << std::endl;
            } else {
                std::cout << "Недостаточно FarmCoin для полива!" << std::endl;
                return;
            }
        }
    }
}

void fertilizePlant(int bedIndex) {
    if (bedIndex < 0 || bedIndex >= currentBedCount) return;
    spendMoney(FERTILIZER_COST);
    for (auto& plant : beds[bedIndex]) {
        if (plant.growthStage > 0 && plant.growthStage < 3) {
            plant.hasFertilizer = true;
            plant.growthStage++;
        }
    }
}


bool addNewBed() {
    if (currentBedCount >= MAX_BEDS) return false;
    if (!canAfford(BED_PRICE)) return false;

    spendMoney(BED_PRICE);

    // Рассчитываем позицию в сетке 2x4
    int index = currentBedCount; // Индекс новой грядки (0 - первая, 7 - последняя)
    int row = index / 2;  // Номер строки (0, 1, 2, 3)
    int col = index % 2;  // Номер столбца (0 или 1)

    float startX = 480.0f;
    float startY = 200.0f;
    float offsetX = 300.0f;
    float offsetY = 150.0f;

    gardenBeds[currentBedCount].position = sf::Vector2f(startX + col * offsetX, startY + row * offsetY);

    std::cout << "bed was added " << currentBedCount + 1
              << " in position (" << gardenBeds[currentBedCount].position.x
              << ", " << gardenBeds[currentBedCount].position.y << ")" << std::endl;

    currentBedCount++;
    return true;
}

// Отрисовка игровых объектов
void renderGame(sf::RenderWindow& window) {
    const int index = currentBedCount; // Индекс новой грядки (0 - первая, 7 - последняя)
    const int row = index / 2;  // Номер строки (0, 1, 2, 3)
    const int col = index % 2;
    const float bedWidth = 3.0f;
    const float bedHeight = 3.0f;
    const float startX = 480.0f;
    const float startY = 100.0f;
    const float offsetX = 250.0f;
    const float offsetY = 150.0f;
    const float plantXOffset = 20.0f;
    const float plantYOffset = -25.0f;
    const float plantSpacing = 400.0f;
    const float BED_SCALE = 3.0f;
    const float PLANT_SCALE = 3.5f; // Масштаб растений
    constexpr float PLANT_SPACING_X = 80.f; // Расстояние !!!
    constexpr float PLANT_SPACING_Y = 30.f;

    for (int i = 0; i < currentBedCount; ++i) {
        sf::Sprite bedSprite(bedTexture);
        bedSprite.setScale(bedWidth, bedHeight);
        bedSprite.setPosition(gardenBeds[i].position);
        bedSprite.setPosition(startX + (i % 2) * offsetX, startY + (i / 2) * offsetY);

        window.draw(bedSprite);

        for (int plantIdx = 0; plantIdx < PLANTS_PER_BED; ++plantIdx) {
            if (beds[i][plantIdx].growthStage > 0) {
                sf::Sprite plantSprite;

                switch(beds[i][plantIdx].growthStage) {
                    case 1: plantSprite.setTexture(plant1Texture); break;
                    case 2: plantSprite.setTexture(plant2Texture); break;
                    case 3: plantSprite.setTexture(plant3Texture); break;
                }

                constexpr float BED_WIDTH = 200.0f; // Ширина грядки
                constexpr float BED_HEIGHT = 100.0f; // Высота грядки

                float startX = 480.0f;  // Координаты первой грядки
                float startY = 200.0f;

                float plantX = startX + (i % 2) * (BED_WIDTH + PLANT_SPACING_X) + (plantIdx * PLANT_SPACING_X);
                float plantY = startY + (i / 2) * (BED_HEIGHT + PLANT_SPACING_Y) - 140.0f; //140 - высота

                plantSprite.setScale(PLANT_SCALE, PLANT_SCALE);
                plantSprite.setPosition(plantX, plantY);
                window.draw(plantSprite);
            }
        }
    }
}

// Обновление игрового состояния
void updateGame(float deltaTime) {
    for (auto& bed : beds) {
        for (auto& plant : bed) {
            if (plant.growthStage > 0 && plant.growthStage < 3) {

                float growthRate = 0.05f * deltaTime;

                if (plant.isWatered) growthRate *= 1.8f;
                if (plant.hasFertilizer) growthRate *= 1.3f;

                growthRate *= (0.9f + 0.2f * (rand() % 100) / 100.0f);

                plant.growthStage = std::min(plant.growthStage + growthRate, 3.0f);

                plant.isWatered = false;
                plant.hasFertilizer = false;
            }
        }
    }

    static float timeSinceLastUpdate = 0.0f;
    timeSinceLastUpdate += deltaTime;
    if (timeSinceLastUpdate >= 5.0f) {
        updateFarmCoinRate();
        timeSinceLastUpdate = 0.0f;
    }
}


void waterBed(int bedIndex) {
    if (bedIndex >= 0 && bedIndex < currentBedCount) {
        for (auto& plant : beds[bedIndex]) {
            plant.isWatered = true;
        }
    }
}
