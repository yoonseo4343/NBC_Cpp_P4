#include <iostream>
#include <vector>
#include <string>
#include <map>
#include "PotionRecipe.h"
#include "RecipeManager.h"
#include "StockManager.h"

int main() {
    RecipeManager recipeMng;
    StockManager stockMng;

    while (true) {
        std::cout << "-{{ 연금술 공방 관리 시스템 }}-" << std::endl;
        std::cout << "1. 레시피 추가" << std::endl;
        std::cout << "2. 모든 레시피 출력" << std::endl;
        std::cout << "3. 물약 이름으로 레시피 검색" << std::endl;
        std::cout << "4. 물약 재료로 레시피 검색" << std::endl;
        std::cout << "5. 물약 재고 검색" << std::endl;
        std::cout << "6. 공병 반환" << std::endl;
        std::cout << "0. 종료" << std::endl;
        std::cout << "선택: ";

        int choice;
        std::cin >> choice;

        if (std::cin.fail()) {
            std::cout << "잘못된 입력입니다. 숫자를 입력해주세요." << std::endl;
            std::cin.clear();
            std::cin.ignore(10000, '\n');
            continue;
        }

        if (choice == 1) {
            std::string name;
            std::cout << "물약 이름: ";
            std::cin.ignore(10000, '\n');
            std::getline(std::cin, name);

            // 여러 재료를 입력받기 위한 로직
            std::vector<std::string> ingredients_input;
            std::string ingredient;
            std::cout << "필요한 재료들을 입력하세요. (입력 완료 시 '끝' 입력)" << std::endl;

            while (true) {
                std::cout << "재료 입력: ";
                std::getline(std::cin, ingredient);

                // 사용자가 '끝'을 입력하면 재료 입력 종료
                if (ingredient == "끝") {
                    break;
                }
                ingredients_input.push_back(ingredient);
            }

            // 입력받은 재료가 하나 이상 있을 때만 레시피 추가
            if (!ingredients_input.empty()) {
                //recipeMng.addRecipe(name, ingredients_input);
                stockMng.initializeStock(recipeMng.addRecipe(name, ingredients_input)->potionName); // 초기 재고 세팅
            }
            else {
                std::cout << ">> 재료가 입력되지 않아 레시피 추가를 취소합니다." << std::endl;
            }

        }
        else if (choice == 2) {
            recipeMng.displayAllRecipes();

        }
        else if (choice == 3) {
            std::string name;
            std::cout << "물약 이름: ";
            std::cin >> name;
            PotionRecipe* tempC = recipeMng.findRecipeByName(name);
            if (tempC) {
                //출력
                tempC->displayRecipe();
                if (stockMng.dispensePotion(tempC->potionName))
                    std::cout << ">> '" << tempC->potionName << "'이(가) 1개 지급되었습니다.\n";
            }
            else
                std::cout << ">> 검색 결과가 없습니다." << std::endl;
        }
        else if (choice == 4) {
            std::string ingredients;
            std::cout << "물약 재료: ";
            std::cin >> ingredients;
            //재료가 포함된 모든 레시피를 벡터에 저장해서 레시피 이름 출력
            std::vector<PotionRecipe> vec = recipeMng.findRecipeByIngredient(ingredients);
            if (vec.empty()) {
                std::cout << ">> 검색 결과가 없습니다." << std::endl;
            }
            else {
                std::cout << "----- [ 관련 레시피 ] -----" << std::endl;
                for (size_t i = 0; i < vec.size(); i++) {
                    std::cout << "- " << vec[i].potionName << std::endl;
                }
                std::cout << "---------------------------\n";
                for (size_t i = 0; i < vec.size(); i++) {
                    if (stockMng.dispensePotion(vec[i].potionName))
                        std::cout << ">> '" << vec[i].potionName << "'이(가) 1개 지급되었습니다.\n";
                }
            }
        }
        else if (choice == 5) {
            std::string name;
            std::cout << "조회할 물약 이름: ";
            std::cin >> name;
            std::cout <<">> " << stockMng.getStock(name) << "개 있습니다.\n";
        }
        else if (choice == 6) {
            std::string name;
            std::cout << "반환할 물약 이름: ";
            std::cin >> name;
            stockMng.returnPotion(name);
        }
        else if (choice == 0) {
            std::cout << "공방 문을 닫습니다..." << std::endl;
            break;

        }
        else {
            std::cout << "잘못된 선택입니다. 다시 시도하세요." << std::endl;
        }
    }

    return 0;
}