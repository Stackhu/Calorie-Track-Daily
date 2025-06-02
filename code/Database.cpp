#include "Database.h"
#include "Utils.h"

#include <stdexcept>
#include <sstream>

User UserDatabase::parseCSVLine(const std::string& line) const {
    auto tokens = Utils::split(line, ',');
    if (tokens.size() < 5) {
        throw std::runtime_error("Invalid user record format");
    }
    return User(tokens[0], std::stoi(tokens[1]), tokens[2][0],
                std::stod(tokens[3]), std::stod(tokens[4]));
}

std::string UserDatabase::toCSVLine(const User& item) const {
    return item.getName() + "," +
           std::to_string(item.getAge()) + "," +
           std::string(1, item.getGender()) + "," +
           std::to_string(item.getHeight()) + "," +
           std::to_string(item.getWeight());
}

std::string UserDatabase::getCSVHeader() const {
    return "Name,Age,Gender,Height,Weight";
}

Food FoodDatabase::parseCSVLine(const std::string& line) const {
    auto tokens = Utils::split(line, ',');
    if (tokens.size() < 3) {
        throw std::runtime_error("Invalid food record format");
    }
    return Food(tokens[0], std::stod(tokens[1]),
                Food::stringToCategory(tokens[2]));
}

std::string FoodDatabase::toCSVLine(const Food& item) const {
    return item.getName() + "," +
           std::to_string(item.getCaloriesPer100g()) + "," +
           Food::categoryToString(item.getCategory());
}

std::string FoodDatabase::getCSVHeader() const {
    return "Food Name,Calories (kcal/100g),Category";
}

DietRecord DietRecordDatabase::parseCSVLine(const std::string& line) const {
    auto tokens = Utils::split(line, ',');
    if (tokens.size() < 5) {
        throw std::runtime_error("Invalid diet record format");
    }
    Date date(tokens[0]);
    Food food(tokens[2], std::stod(tokens[3]),
              Food::stringToCategory(tokens[1]));
    return DietRecord(date, food, std::stod(tokens[4]));
}

std::string DietRecordDatabase::toCSVLine(const DietRecord& item) const {
    return item.getDate().toString() + "," +
           Food::categoryToString(item.getFood().getCategory()) + "," +
           item.getFood().getName() + "," +
           std::to_string(item.getFood().getCaloriesPer100g()) + "," +
           std::to_string(item.getWeight());
}

std::string DietRecordDatabase::getCSVHeader() const {
    return "Date,Category,Food Name,Calories (kcal/100g),Weight (g)";
}
