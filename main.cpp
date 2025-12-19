#include <iostream>
#include <vector>
#include <string>
#include <map>

// PotionRecipe 클래스: 재료 목록을 vector<string>으로 변경
class PotionRecipe {
public:
    std::string potionName;
    std::vector<std::string> ingredients; // 단일 재료에서 재료 '목록'으로 변경
    PotionRecipe() {}
    // 생성자: 재료 목록을 받아 초기화하도록 수정
    PotionRecipe(const std::string& name, const std::vector<std::string>& ingredients)
        : potionName(name), ingredients(ingredients) {
    }
    bool isValid() const {
        if (potionName == "")
            return false;
        else
            return true;
    }
    void displayRecipe() {
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
};

// AlchemyWorkshop 클래스: 레시피 목록을 관리 - > 레시피 매니저
class RecipeManager {
private:
    std::vector<PotionRecipe> recipes;

public:
    // addRecipe 메서드: 재료 목록(vector)을 매개변수로 받도록 수정
    PotionRecipe* addRecipe(const std::string& name, const std::vector<std::string>& ingredients) {
        recipes.push_back(PotionRecipe(name, ingredients));
        std::cout << ">> 새로운 레시피 '" << name << "'이(가) 추가되었습니다." << std::endl;
        return &recipes.back();
    }

    // 모든 레시피 출력 메서드
    void displayAllRecipes() const {
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
    PotionRecipe* findRecipeByName(std::string name) {
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
    std::vector<PotionRecipe> findRecipeByIngredient(std::string ingredient) {
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
};
//재고 관리 매니저
class StockManager {
private:
    std::map<std::string, int> potionStock;
    const int MAX_STOCK = 3;
public:
    void initializeStock(std::string potionName) {
        //레시피가 공방에 추가될때 호출되는 함수
        potionStock[potionName] = MAX_STOCK;
        std::cout << ">> 재고 "<<MAX_STOCK<<"개가 추가되었습니다." << std::endl;
    }
    bool dispensePotion(std::string potionName) {
        //재고 1개 이상이면 true 아니면 false 반환
        if (potionStock[potionName] > 0) {
            potionStock[potionName]--; // 1개 지급
            return true;
        }
        else
            return false;
    }
    void returnPotion(std::string  potionName) {
        //공병 반환 시 호출
        if (potionStock.count(potionName)) {
            if (potionStock[potionName] < MAX_STOCK)
            {
                potionStock[potionName] += 1;
                std::cout <<">> "<< potionName << " 공병을 반환합니다.\n";
            }
            else
                std::cout << ">> 최대 재고를 초과하여 반환할 수 없습니다.\n";
        }
        else
            std::cout << ">> 반환할 수 없는 공병입니다.\n";
    }
    int getStock(std::string potionName) {
        if (potionStock.count(potionName)) {
            return potionStock[potionName];
        }
        else {
            return 0;
        }
    }
};
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