// textures.h
#ifndef TEXTURES_H
#define TEXTURES_H

#include <SFML/Graphics.hpp>

// Основные текстуры
extern sf::Texture groundTexture;
extern sf::Texture bedTexture;
extern sf::Texture plant1Texture;
extern sf::Texture plant2Texture;
extern sf::Texture plant3Texture;

// UI текстуры (кнопки)
extern sf::Texture waterTexture;
extern sf::Texture fertilizerTexture;
extern sf::Texture sellTexture;
extern sf::Texture loanTexture;
extern sf::Texture leverageTexture;
extern sf::Texture bedBuyTexture;
extern sf::Texture seedTexture;

bool loadAllTextures();

#endif