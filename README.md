# CryptoFarm

**CryptoFarm** — a fun C++ console-based academic project where you manage a virtual farming business. Starting with **1500 FarmCoins**, your goal is to buy planting beds, grow plants, and sell the harvest at prices dynamically tied to a chosen cryptocurrency’s real-time rate from **Binance**.

---

##  Concept & Gameplay

You begin with a limited budget and make strategic decisions:
- Purchase beds (slots), each mapped to keyboard keys: **1**, **2**, **3**, …
- Grow plants using watering and fertilizer actions tied to each bed
- Finally, sell fully grown plants. Their sale price fluctuates based on live Binance exchange rates of a selected cryptocurrency

The game simulates balancing resource management (beds, water, fertilizer) with market timing (crypto rate), making it both educational and engaging.

---

##  Game Rules

1. **Start Budget**: 1500 FarmCoins  
2. **Buying Beds**: Press numeric keys (`1`, `2`, …) to acquire and activate planting beds  
3. **Growing Plants**: Use watering and fertilizer commands to nurture plants in active beds  
4. **Selling Harvest**: When ready, sell plants. Market price adjusts dynamically based on Binance API crypto rate  
5. **Goal**: Maximize your FarmCoins through optimal farming and timing

---
<img width="1186" height="814" alt="image" src="https://github.com/user-attachments/assets/68aff876-a768-4e09-92db-b005097945c4" />
---

##  Purpose & Academic Context

This project was developed as a **C++ course final** to showcase:
- Console-based UI and keyboard interaction
- Real-world API integration (fetching Binance rates)
- Strategic resource-management gameplay
- Practical C++ structuring and code clarity

---

##  Getting Started

### Requirements

- A C++17-capable compiler (e.g., GCC, Clang, or Visual Studio)
- Access to the internet to fetch real-time rates from Binance API

### Installation & Run

```bash
git clone https://github.com/kihaas/game-cryptofarm.git
cd game-cryptofarm

# Build (example with g++)
g++ -std=c++17 main.cpp -o CryptoFarm

# Run
./CryptoFarm


