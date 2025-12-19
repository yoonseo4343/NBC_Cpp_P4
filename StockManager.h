#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "PotionRecipe.h"

//재고 관리 매니저
class StockManager {
private:
    std::map<std::string, int> potionStock;
    const int MAX_STOCK = 3;
public:
    void initializeStock(std::string potionName);
    bool dispensePotion(std::string potionName);
    void returnPotion(std::string  potionName);
    int getStock(std::string potionName);
};