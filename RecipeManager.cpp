#include "RecipeManager.h"

// addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
PotionRecipe* RecipeManager::addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
    recipes.push_back(PotionRecipe(name, ingredients));
    std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다." << std::endl;
    return &recipes.back();
}

// 모든 레시피 출력 메서드
void RecipeManager::displayAllRecipes() const {
    if (recipes.empty()) {
        std::cout << "아직 등록된 레시피가 없습니다." << std::endl;
        return;
    }

    std::cout << "\n--- [ 전체 레시피 목록 ] ---" << std::endl;
    for (size_t i = 0; i < recipes.size(); ++i) {
        std::cout << "- 물약 이름: " << recipes[i].potionName << std::endl;
        std::cout << "  > 필요 재료: ";

        // 재료 목록을 순회하며 출력
        for (size_t j = 0; j < recipes[i].ingredients.size(); ++j) {
            std::cout << recipes[i].ingredients[j];
            // 마지막 재료가 아니면 쉼표로 구분
            if (j < recipes[i].ingredients.size() - 1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
    std::cout << "---------------------------\n";
}
//물약 이름 검색
PotionRecipe* RecipeManager::findRecipeByName(std::string name) {
    if (recipes.empty()) {
        return nullptr;
    }
    //레시피 목록 순회
    for (size_t i = 0; i < recipes.size(); i++) {
        if (recipes[i].potionName == name) {
            return &recipes[i];
        }
        else if (i == recipes.size() - 1) {
            return nullptr;
        }
    }
    return nullptr;
}
//물약 재료 검색
std::vector<PotionRecipe> RecipeManager::findRecipeByIngredient(std::string ingredient) {
    if (recipes.empty()) {
        return {};
    }
    //레시피 목록 순회
    std::vector<PotionRecipe> tempVec;
    for (size_t i = 0; i < recipes.size(); i++) {
        //재료 순회
        for (size_t j = 0; j < recipes[i].ingredients.size(); j++) {
            if (recipes[i].ingredients[j] == ingredient) {
                tempVec.push_back(recipes[i]);
            }
        }
    }
    return tempVec;
}