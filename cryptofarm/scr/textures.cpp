#include "../include/textures.h"
#include <iostream>
#include <SFML/Graphics.hpp>


sf::Texture groundTexture;
sf::Texture bedTexture;
sf::Texture plant1Texture;
sf::Texture plant2Texture;
sf::Texture plant3Texture;


// UI текстуры (7 кнопок)
sf::Texture waterTexture;
sf::Texture fertilizerTexture;
sf::Texture sellTexture;
sf::Texture loanTexture;
sf::Texture leverageTexture;  // Кредитное плечо
sf::Texture bedBuyTexture;    // Покупка грядок
sf::Texture seedTexture;


bool loadAllTextures() {
    // Основные текстуры
    groundTexture.loadFromFile("../assets/sprites/ground.png");
    bedTexture.loadFromFile("../assets/sprites/bed.png");
    plant1Texture.loadFromFile("../assets/sprites/plant1.png");
    plant2Texture.loadFromFile("../assets/sprites/plant2.png");
    plant3Texture.loadFromFile("../assets/sprites/plant3.png");
    waterTexture.loadFromFile("../assets/sprites/water.png");
    fertilizerTexture.loadFromFile("../assets/sprites/fertilizer.png");
    sellTexture.loadFromFile("../assets/sprites/sell.png");
    loanTexture.loadFromFile("../assets/sprites/loan.png");
    leverageTexture.loadFromFile("../assets/sprites/leverage.png");  // Кредитное плечо
    bedBuyTexture.loadFromFile("../assets/sprites/bed_buy.png");     // Покупка грядок
    seedTexture.loadFromFile("../assets/sprites/seed.png");


    return true;
}
