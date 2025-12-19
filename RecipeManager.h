#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "PotionRecipe.h"

// AlchemyWorkshop 클래스: 레시피 목록을 관리 - > 레시피 매니저
class RecipeManager {
private:
    std::vector<PotionRecipe> recipes;

public:
    // addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
    PotionRecipe* addRecipe(const std::string& name, const std::vector<std::string>& ingredients);

    // 모든 레시피 출력 메서드
    void displayAllRecipes() const;
    //물약 이름 검색
    PotionRecipe* findRecipeByName(std::string name);
    //물약 재료 검색
    std::vector<PotionRecipe> findRecipeByIngredient(std::string ingredient);
};