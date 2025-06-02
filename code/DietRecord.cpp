#include "Database.h"
#include "Date.h"
#include "DietRecord.h"
#include "Food.h"
#include "Menu.h"
#include "User.h"
#include "Utils.h"

DietRecord::DietRecord() 
    : date(), food(), weight(0.0), calories(0.0) {}

DietRecord::DietRecord(const Date& date, const Food& food, double weight)
    : date(date), food(food), weight(weight) {
    calories = calculateCalories();
}

double DietRecord::calculateCalories() const {
    return food.getCaloriesPer100g() * (weight / 100.0);
}

Date DietRecord::getDate() const { return date; }
Food DietRecord::getFood() const { return food; }
double DietRecord::getWeight() const { return weight; }
double DietRecord::getCalories() const { return calories; }