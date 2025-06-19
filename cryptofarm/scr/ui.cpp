#include "../include/ui.h"
#include "../include/textures.h"
#include "../include/economy.h"
#include "../include/game_logic.h" // Добавлен include
#include <iostream>
#include <iomanip> // Для std::fixed и std::setprecision
#include <sstream> // Для std::stringstream

sf::Sprite waterButton;
sf::Sprite fertilizerButton;
sf::Sprite sellButton;
sf::Sprite loanButton;
sf::Sprite leverageButton;
sf::Sprite bedBuyButton;
sf::Sprite seedButton;

sf::Font font;
sf::Text balanceText;
sf::Text rateText;

void initUI() {
    if (!font.loadFromFile("../assets/fonts/font.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
    }

    balanceText.setFont(font);
    balanceText.setCharacterSize(24);
    balanceText.setFillColor(sf::Color::White);
    balanceText.setPosition(10, 10);

    rateText.setFont(font);
    rateText.setCharacterSize(24);
    rateText.setFillColor(sf::Color::White);
    rateText.setPosition(10, 40);

    const float buttonX = 1000.0f;
    float buttonY = 100.0f;
    const float buttonSpacing = 70.0f;

    waterButton.setTexture(waterTexture);
    waterButton.setPosition(buttonX, buttonY);
    buttonY += buttonSpacing;

    fertilizerButton.setTexture(fertilizerTexture);
    fertilizerButton.setPosition(buttonX, buttonY);
    buttonY += buttonSpacing;

    sellButton.setTexture(sellTexture);
    sellButton.setPosition(buttonX, buttonY);
    buttonY += buttonSpacing;

    loanButton.setTexture(loanTexture);
    loanButton.setPosition(buttonX, buttonY);
    buttonY += buttonSpacing;

    leverageButton.setTexture(leverageTexture);
    leverageButton.setPosition(buttonX, buttonY);
    buttonY += buttonSpacing;

    bedBuyButton.setTexture(bedBuyTexture);
    bedBuyButton.setPosition(buttonX, buttonY);
    buttonY += buttonSpacing;

    seedButton.setTexture(seedTexture);
    seedButton.setPosition(buttonX, buttonY);
}

void handleUIEvents(sf::Event& event, sf::RenderWindow& window) {
    if (event.type == sf::Event::MouseButtonPressed) {
        sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));

        if (waterButton.getGlobalBounds().contains(mousePos)) {
            std::cout << "Water button clicked" << std::endl;
        }
        else if (fertilizerButton.getGlobalBounds().contains(mousePos)) {
            std::cout << "Fertilizer button clicked" << std::endl;
        }
        else if (sellButton.getGlobalBounds().contains(mousePos)) {
            std::cout << "Sell button clicked" << std::endl;
        }
        else if (loanButton.getGlobalBounds().contains(mousePos)) {
            std::cout << "Loan button clicked" << std::endl;
        }
        else if (leverageButton.getGlobalBounds().contains(mousePos)) {
            std::cout << "Leverage button clicked" << std::endl;
        }
        else if (bedBuyButton.getGlobalBounds().contains(mousePos)) {
            if (addNewBed()) {
                std::cout << "The garden bed has been bought!" << std::endl;
            } else {
                std::cout << "Failed to buy a garden bed" << std::endl;
            }
        }
        else if (seedButton.getGlobalBounds().contains(mousePos)) {
            std::cout << "Seed button clicked" << std::endl;
        }
    }
}

void drawPriceChart(sf::RenderWindow& window) {
    const float chartX = 50.0f;
    const float chartY = 100.0f;
    const float chartWidth = 400.0f;
    const float chartHeight = 600.0f;

    // Фон графика
    sf::RectangleShape chartBackground(sf::Vector2f(chartWidth, chartHeight));
    chartBackground.setPosition(chartX, chartY);
    chartBackground.setFillColor(sf::Color(30, 30, 40));
    window.draw(chartBackground);

    // Граница
    sf::RectangleShape chartBorder(sf::Vector2f(chartWidth, chartHeight));
    chartBorder.setPosition(chartX, chartY);
    chartBorder.setFillColor(sf::Color::Transparent);
    chartBorder.setOutlineColor(sf::Color::White);
    chartBorder.setOutlineThickness(1.0f);
    window.draw(chartBorder);

    // Подпись графика
    sf::Text chartTitle("FarmCoin Price", font, 18);
    chartTitle.setPosition(chartX + 10, chartY + 10);
    chartTitle.setFillColor(sf::Color::White);
    window.draw(chartTitle);
}

void renderUI(sf::RenderWindow& window) {
    // Обновление текстовых полей
    balanceText.setString("Balance: " + std::to_string((int)getPlayerBalance()) + " FC");

    // Форматирование курса с 2 знаками после запятой
    std::stringstream rateStream;
    rateStream << std::fixed << std::setprecision(2) << getFarmCoinRate();
    rateText.setString("Rate: " + rateStream.str() + "%");

    // Отрисовка текста
    window.draw(balanceText);
    window.draw(rateText);

    // Отрисовка всех кнопок
    window.draw(waterButton);
    window.draw(fertilizerButton);
    window.draw(sellButton);
    window.draw(loanButton);
    window.draw(leverageButton);
    window.draw(bedBuyButton);
    window.draw(seedButton);

    // Отрисовка графика
    drawPriceChart(window);

    // Подписи к кнопкам
    auto drawButtonLabel = [&](const std::string& text, float y) {
        sf::Text label(text, font, 18);
        label.setPosition(1050.0f, y + 10.0f);
        label.setFillColor(sf::Color::White);
        window.draw(label);
    };

    drawButtonLabel("Water", 100.0f);
    drawButtonLabel("Fertilizer", 170.0f);
    drawButtonLabel("Sell", 240.0f);
    drawButtonLabel("Loan", 310.0f);
    drawButtonLabel("Leverage", 380.0f);
    drawButtonLabel("Buy Bed", 450.0f);
    drawButtonLabel("Buy Seed", 520.0f);
}