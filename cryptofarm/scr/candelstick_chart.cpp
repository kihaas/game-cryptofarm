//binance +-
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include "C:/Users/qwert/CLionProjects/aaaa/curl-master/include/curl/curl.h"
#include "C:\Users\qwert\CLionProjects\aaaa\json-3.11.3\single_include\nlohmann\json.hpp"


using json = nlohmann::json;

// Функция для обработки данных от cURL
size_t WriteCallback(void* contents, size_t size, size_t nmemb, std::string* output) {
    output->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Функция для запроса данных с Binance API
std::string getBinanceData() {
    CURL* curl = curl_easy_init();
    std::string response;

    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, "https://api.binance.com/api/v3/klines?symbol=BTCUSDT&interval=1m&limit=50");
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &response);
        curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return response;
}

// Структура свечи
struct Candle {
    float open, high, low, close;
};

// Функция для парсинга JSON в свечи
std::vector<Candle> parseCandles(const std::string& jsonData) {
    std::vector<Candle> candles;
    auto data = json::parse(jsonData);

    for (const auto& item : data) {
        Candle c;
        c.open = std::stof(item[1].get<std::string>());
        c.high = std::stof(item[2].get<std::string>());
        c.low = std::stof(item[3].get<std::string>());
        c.close = std::stof(item[4].get<std::string>());
        candles.push_back(c);
    }
    return candles;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(600, 400), "Candlestick Chart");

    std::vector<Candle> candles = parseCandles(getBinanceData());
    sf::Clock clock; // Таймер для обновления раз в минуту

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Обновляем данные раз в минуту
        if (clock.getElapsedTime().asSeconds() > 60) {
            candles = parseCandles(getBinanceData());
            clock.restart();
        }

        window.clear(sf::Color::Black);

        // Рисуем свечи
        float candleWidth = 10.0f;
        float x = 10.0f;
        float maxPrice = 0.0f, minPrice = 1e6f;

        for (const auto& c : candles) {
            if (c.high > maxPrice) maxPrice = c.high;
            if (c.low < minPrice) minPrice = c.low;
        }

        for (const auto& c : candles) {
            float openY = 350 - ((c.open - minPrice) / (maxPrice - minPrice)) * 300;
            float closeY = 350 - ((c.close - minPrice) / (maxPrice - minPrice)) * 300;
            float highY = 350 - ((c.high - minPrice) / (maxPrice - minPrice)) * 300;
            float lowY = 350 - ((c.low - minPrice) / (maxPrice - minPrice)) * 300;

            sf::RectangleShape body(sf::Vector2f(candleWidth, std::abs(closeY - openY)));
            body.setPosition(x, std::min(openY, closeY));
            body.setFillColor((c.close >= c.open) ? sf::Color::Green : sf::Color::Red);

            sf::RectangleShape wick(sf::Vector2f(2, highY - lowY));
            wick.setPosition(x + candleWidth / 2, lowY);
            wick.setFillColor(sf::Color::White);

            window.draw(wick);
            window.draw(body);

            x += candleWidth + 5;
        }

        window.display();
    }

    return 0;
}