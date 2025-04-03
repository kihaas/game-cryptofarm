#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <windows.h>
#include <vector>
#include "../include/game_logic.h"
#include "../include/ui.h"
#include "../include/economy.h"
#include "../include/textures.h"




int main() {
    system("chcp 1251");
    sf::RenderWindow window(sf::VideoMode(1200, 800), "CryptoFarm");
    window.setFramerateLimit(60);

    if (!loadAllTextures()) {
        std::cerr << "Failed to load textures!" << std::endl;
        return -1;
    }


    initEconomy();
    initGame();
    initUI();


    sf::Texture groundTexture;
    if (!groundTexture.loadFromFile("../assets/sprites/ground.png")) {
        std::cerr << "Failed to load ground texture!" << std::endl;
        return -1;
    }
    groundTexture.setSmooth(false);
    sf::Sprite groundSprite(groundTexture);
    sf::Sprite bedSprite(bedTexture);
    sf::Sprite plantSprite(plant1Texture);




    sf::Clock clock;
    float deltaTime = 0.0f;


    while (window.isOpen()) {
        deltaTime = clock.restart().asSeconds();




        // Обработка событий
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }
            handleUIEvents(event, window);  // Обработка событий UI
        }


        // Обновление игровой логики
        updateGame(deltaTime);


        // Отрисовка
        window.clear();


        // Рисуем фон плитками
        for (int y = 0; y < window.getSize().y; y += groundTexture.getSize().y) {
            for (int x = 0; x < window.getSize().x; x += groundTexture.getSize().x) {
                groundSprite.setPosition(static_cast<float>(x), static_cast<float>(y));
                window.draw(groundSprite);
            }
        }


        // Рисуем игровые объекты и UI
        renderGame(window);
        renderUI(window);


        window.display();
    }


    return 0;
}
