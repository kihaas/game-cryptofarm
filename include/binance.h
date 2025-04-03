#ifndef BINANCE_H
#define BINANCE_H

#include <string>
#include <vector>

// Параметры для фильтрации
const double MIN_VOLUME = 100000;  // Минимальный 24h торговый объем
const double MIN_PRICE = 0.1;       // Минимальная цена для фильтрации пар
const double CORRELATION_THRESHOLD = 0.5;  // Минимальный порог корреляции
const double STD_DEV_THRESHOLD = 0.02;      // Максимально допустимое стандартное отклонение для спреда

// Функция для получения данных с Binance API
std::string fetch_binance_data(const std::string& url);

// Функция для получения исторических данных
std::vector<double> fetch_historical_data(const std::string& symbol, const std::string& interval = "1d", int limit = 100);

// Функция для расчета корреляции
double calculate_correlation(const std::vector<double>& prices1, const std::vector<double>& prices2);

// Функция для расчета стандартного отклонения спреда
double calculate_std_dev(const std::vector<double>& prices1, const std::vector<double>& prices2);

// Функция для визуализации графиков
void plot_graph(const std::vector<double>& prices1, const std::vector<double>& prices2, const std::vector<double>& spread);

// Основная функция для фильтрации торговых пар
void filter_trading_pairs();

#endif // BINANCE_H