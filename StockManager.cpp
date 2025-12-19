#include "StockManager.h"

void StockManager::initializeStock(std::string potionName) {
    //레시피가 공방에 추가될때 호출되는 함수
    potionStock[potionName] = MAX_STOCK;
    std::cout << ">> 재고 " << MAX_STOCK << "개가 추가되었습니다." << std::endl;
}
bool StockManager::dispensePotion(std::string potionName) {
    //재고 1개 이상이면 true 아니면 false 반환
    if (potionStock[potionName] > 0) {
        potionStock[potionName]--; // 1개 지급
        return true;
    }
    else
        return false;
}
void StockManager::returnPotion(std::string  potionName) {
    //공병 반환 시 호출
    if (potionStock.count(potionName)) {
        if (potionStock[potionName] < MAX_STOCK)
        {
            potionStock[potionName] += 1;
            std::cout << ">> '" << potionName << "' 공병을 반환합니다.\n";
        }
        else
            std::cout << ">> 최대 재고를 초과하여 반환할 수 없습니다.\n";
    }
    else
        std::cout << ">> 반환할 수 없는 공병입니다.\n";
}
int StockManager::getStock(std::string potionName) {
    if (potionStock.count(potionName)) {
        return potionStock[potionName];
    }
    else {
        return 0;
    }
}
