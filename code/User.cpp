#include "Database.h"
#include "Date.h"
#include "DietRecord.h"
#include "Food.h"
#include "Menu.h"
#include "User.h"
#include "Utils.h"

#include <cmath>
#include <stdexcept>

User::User() 
    : name(""), age(0), gender(' '), height(0.0), weight(0.0) {}

User::User(const std::string& name, int age, char gender, 
           double height, double weight)
    : name(name), age(age), gender(gender), height(height), weight(weight) {
    if (gender != 'M' && gender != 'F') {
        throw std::invalid_argument("Gender must be 'M' or 'F'");
    }
}

double User::calculateBMI() const {
    if (height <= 0) return 0.0;
    return weight / pow(height / 100.0, 2);
}

double User::calculateBMR() const {
    if (gender == 'M') {
        return 10 * weight + 6.25 * height - 5 * age + 5;
    } else {
        return 10 * weight + 6.25 * height - 5 * age - 161;
    }
}

double User::calculateDailyCalories() const {
    return calculateBMR() * 1.2;  // 轻度活动系数
}

std::string User::getBMICategory() const {
    double bmi = calculateBMI();
    if (bmi < 18.5) return "Underweight";
    if (bmi < 24) return "Normal";
    if (bmi < 28) return "Overweight";
    return "Obesity";
}

// 访问器和修改器实现
std::string User::getName() const { return name; }
int User::getAge() const { return age; }
char User::getGender() const { return gender; }
double User::getHeight() const { return height; }
double User::getWeight() const { return weight; }

void User::setName(const std::string& name) { this->name = name; }
void User::setAge(int age) { this->age = age; }
void User::setGender(char gender) { 
    if (gender == 'M' || gender == 'F') this->gender = gender; 
}
void User::setHeight(double height) { this->height = height; }
void User::setWeight(double weight) { this->weight = weight; }