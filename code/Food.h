#ifndef FOOD_H
#define FOOD_H

#include <string>

enum class FoodCategory {
    STAPLE_FOOD,    // 主食
    ANIMAL_PROTEIN, // 肉禽蛋
    VEGETABLES,     // 蔬菜
    FRUITS,         // 水果
    BEVERAGES       // 饮料
};

class Food {
public:
    Food();
    Food(const std::string& name, double caloriesPer100g, FoodCategory category);
    
    // 访问器
    std::string getName() const;
    double getCaloriesPer100g() const;
    FoodCategory getCategory() const;
    
    // 类别字符串转换
    static std::string categoryToString(FoodCategory category);
    static FoodCategory stringToCategory(const std::string& categoryStr);
    
private:
    std::string name;
    double caloriesPer100g;
    FoodCategory category;
};

#endif // FOOD_H