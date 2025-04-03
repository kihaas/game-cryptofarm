#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
#include <numeric> // Для std::accumulate
#include <sstream> // Для std::istringstream
#include "C:/Users/qwert/CLionProjects/aaaa/matplotlib-cpp-master/matplotlibcpp.h"
#include "C:/Users/qwert/CLionProjects/aaaa/curl-master/include/curl/curl.h"
#include "C:/Users/qwert/CLionProjects/aaaa/json-3.11.3/single_include/nlohmann/json.hpp"

namespace plt = matplotlibcpp;

// Параметры для фильтрации
const double MIN_VOLUME = 100000;  // Минимальный 24h торговый объем
const double MIN_PRICE = 0.1;       // Минимальная цена для фильтрации пар
const double CORRELATION_THRESHOLD = 0.5;  // Минимальный порог корреляции
const double STD_DEV_THRESHOLD = 0.02;      // Максимально допустимое стандартное отклонение для спреда

// Функция для обработки ответа от API
size_t WriteCallback(void* contents, size_t size, size_t nmemb, void* userp) {
    ((std::string*)userp)->append((char*)contents, size * nmemb);
    return size * nmemb;
}

// Функция для получения данных с Binance API
std::string fetch_binance_data(const std::string& url) {
    CURL* curl;
    CURLcode res;
    std::string readBuffer;

    curl = curl_easy_init();
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, &readBuffer);
        res = curl_easy_perform(curl);
        curl_easy_cleanup(curl);
    }
    return readBuffer;
}

// Функция для получения исторических данных
std::vector<double> fetch_historical_data(const std::string& symbol, const std::string& interval = "1d", int limit = 100) {
    std::string url = "https://api.binance.com/api/v3/klines?symbol=" + symbol + "&interval=" + interval + "&limit=" + std::to_string(limit);
    std::string response = fetch_binance_data(url);

    std::vector<double> prices;
    nlohmann::json jsonData = nlohmann::json::parse(response);

    for (const auto& candle : jsonData) {
        prices.push_back(candle[4].get<double>()); // Закрывающие цены
    }

    return prices;
}

// Функция для расчета корреляции
double calculate_correlation(const std::vector<double>& prices1, const std::vector<double>& prices2) {
    if (prices1.size() != prices2.size() || prices1.empty()) return 0.0;

    double mean1 = std::accumulate(prices1.begin(), prices1.end(), 0.0) / prices1.size();
    double mean2 = std::accumulate(prices2.begin(), prices2.end(), 0.0) / prices2.size();

    double numerator = 0.0;
    double denominator1 = 0.0;
    double denominator2 = 0.0;

    for (size_t i = 0; i < prices1.size(); ++i) {
        numerator += (prices1[i] - mean1) * (prices2[i] - mean2);
        denominator1 += (prices1[i] - mean1) * (prices1[i] - mean1);
        denominator2 += (prices2[i] - mean2) * (prices2[i] - mean2);
    }

    return numerator / std::sqrt(denominator1 * denominator2);
}

// Функция для расчета стандартного отклонения спреда
double calculate_std_dev(const std::vector<double>& prices1, const std::vector<double>& prices2) {
    std::vector<double> spread(prices1.size());
    for (size_t i = 0; i < prices1.size(); ++i) {
        spread[i] = prices1[i] - prices2[i];
    }
    double mean = std::accumulate(spread.begin(), spread.end(), 0.0) / spread.size();
    double variance = 0.0;
    for (const auto& value : spread) {
        variance += (value - mean) * (value - mean);
    }
    return std::sqrt(variance / spread.size());
}

// Функция для визуализации графиков
void plot_data(const std::vector<double>& prices1, const std::vector<double>& prices2, const std::string& label1, const std::string& label2) {
    plt::figure_size(800, 600);

    // Визуализация первой серии данных
    plt::plot(prices1, label1);

    // Визуализация второй серии данных
    plt::plot(prices2, label2);

    // Настройка графика
    plt::title("Сравнение цен");
    plt::xlabel("Время");
    plt::ylabel("Цена");
    plt::legend();

    // Отображение графика
    plt::show();
}

// Основная функция
int main() {
    // Пример использования
    std::string symbol1 = "BTCUSDT";
    std::string symbol2 = "ETHUSDT";

    // Получение исторических данных
    std::vector<double> prices1 = fetch_historical_data(symbol1);
    std::vector<double> prices2 = fetch_historical_data(symbol2);

    // Проверка корреляции
    double correlation = calculate_correlation(prices1, prices2);
    double std_dev = calculate_std_dev(prices1, prices2);

    // Вывод результатов
    std::cout << "Корреляция между " << symbol1 << " и " << symbol2 << ": " << correlation << std::endl;
    std::cout << "Стандартное отклонение спреда: " << std_dev << std::endl;

    // Визуализация данных
    plot_data(prices1, prices2, symbol1, symbol2);

    return 0;
}