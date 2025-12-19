#include "PotionRecipe.h"

// 생성자: 재료 목록을 받아 초기화하도록 수정
PotionRecipe::PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
    : potionName(name), ingredients(ingredients) {
}
bool PotionRecipe::isValid() const {
    if (potionName == "")
        return false;
    else
        return true;
}
void PotionRecipe::displayRecipe() {
    std::cout << "--- [ '" << potionName << "'의 레시피 ] ---" << std::endl;
    std::cout << "  > 필요 재료: ";
    for (size_t i = 0; i < ingredients.size(); i++) {
        if (i == ingredients.size() - 1)
            std::cout << ingredients[i] << std::endl;
        else
            std::cout << ingredients[i] << ", ";
    }
    std::cout << "---------------------------\n";
}