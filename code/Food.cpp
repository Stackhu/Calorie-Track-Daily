#include "Database.h"
#include "Date.h"
#include "DietRecord.h"
#include "Food.h"
#include "Menu.h"
#include "User.h"
#include "Utils.h"

#include <stdexcept>
#include <map>

Food::Food() 
    : name(""), caloriesPer100g(0.0), category(FoodCategory::STAPLE_FOOD) {}

Food::Food(const std::string& name, double caloriesPer100g, FoodCategory category)
    : name(name), caloriesPer100g(caloriesPer100g), category(category) {}

std::string Food::getName() const { return name; }
double Food::getCaloriesPer100g() const { return caloriesPer100g; }
FoodCategory Food::getCategory() const { return category; }

std::string Food::categoryToString(FoodCategory category) {
    static const std::map<FoodCategory, std::string> categoryMap = {
        {FoodCategory::STAPLE_FOOD, "Staple Food"},
        {FoodCategory::ANIMAL_PROTEIN, "Animal Proteins"},
        {FoodCategory::VEGETABLES, "Vegetables"},
        {FoodCategory::FRUITS, "Fruits"},
        {FoodCategory::BEVERAGES, "Beverages"}
    };
    return categoryMap.at(category);
}

FoodCategory Food::stringToCategory(const std::string& categoryStr) {
    static const std::map<std::string, FoodCategory> stringMap = {
        {"S", FoodCategory::STAPLE_FOOD},
        {"A", FoodCategory::ANIMAL_PROTEIN},
        {"V", FoodCategory::VEGETABLES},
        {"F", FoodCategory::FRUITS},
        {"B", FoodCategory::BEVERAGES},
        {"Staple Food", FoodCategory::STAPLE_FOOD},
        {"Animal Proteins", FoodCategory::ANIMAL_PROTEIN},
        {"Vegetables", FoodCategory::VEGETABLES},
        {"Fruits", FoodCategory::FRUITS},
        {"Beverages", FoodCategory::BEVERAGES}
    };
    return stringMap.at(categoryStr);
}