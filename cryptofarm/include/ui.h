#ifndef UI_H
#define UI_H

#include <SFML/Graphics.hpp>

// Объявления текстур
extern sf::Texture waterTexture;
extern sf::Texture fertilizerTexture;
extern sf::Texture sellTexture;
extern sf::Texture loanTexture;
extern sf::Texture leverageTexture;
extern sf::Texture bedBuyTexture;
extern sf::Texture seedTexture;

// Глобальные UI элементы
extern sf::Sprite waterButton;
extern sf::Sprite fertilizerButton;
extern sf::Sprite sellButton;
extern sf::Sprite loanButton;
extern sf::Sprite leverageButton;
extern sf::Sprite bedBuyButton;
extern sf::Sprite seedButton;

extern sf::Font font;
extern sf::Text balanceText;
extern sf::Text rateText;

// Функции интерфейса
void initUI();
void handleUIEvents(sf::Event& event, sf::RenderWindow& window);
void renderUI(sf::RenderWindow& window);
void drawPriceChart(sf::RenderWindow& window); // Добавлено объявление

#endif