#include "Menu.h"
#include "Database.h"
#include "DietRecord.h"
#include "Food.h"
#include "User.h"
#include "Utils.h"

#include <iostream>
#include <iomanip>
#include <limits>
#include <algorithm>
#include <map>
#include <ctime>
#include <sstream>
#include <fstream>
#include <cctype>

Menu::Menu() 
    : userDB(new UserDatabase("data/user.csv")),
      foodDB(new FoodDatabase("data/food_database.csv")),
      dietRecordDB(new DietRecordDatabase("data/diet_records.csv")),
      currentDate(),
      userExists(false) {
#ifdef _WIN32
    system("if not exist data mkdir data");
    system("if not exist reports mkdir reports");
#else
    system("mkdir -p data");
    system("mkdir -p reports");
#endif
}

void Menu::run() {
    showWelcomeScreen();

    // 加载数据文件（自动创建空文件，无警告）
    userDB->load();
    foodDB->load();
    dietRecordDB->load();

    if (userDB->getAllItems().empty()) {
        std::cout << "\nFirst-time setup detected. Please enter your personal data.\n";
        loadOrCreateUser();
    } else {
        currentUser = userDB->getAllItems()[0];
    }

    showMainMenu();
}

void Menu::showWelcomeScreen() {
    std::string message = " Welcome to Calorie Track Daily ";
    int width = message.length() + 4;

    std::string border(width, '*');
    std::string emptyLine = "*" + std::string(width - 2, ' ') + "*";
    std::string messageLine = "* " + message + " *";

    std::cout << border << std::endl;
    std::cout << emptyLine << std::endl;
    std::cout << messageLine << std::endl;
    std::cout << emptyLine << std::endl;
    std::cout << border << std::endl;
}

void Menu::loadOrCreateUser() {
    std::string name;
    int age;
    char gender;
    double height, weight;

    std::cout << "Name: ";
    std::getline(std::cin, name);

    std::cout << "Age: ";
    std::cin >> age;
    std::cin.ignore();

    std::cout << "Gender(F/M): ";
    std::cin >> gender;
    gender = std::toupper(gender);
    std::cin.ignore();

    std::cout << "Height(cm): ";
    std::cin >> height;
    std::cin.ignore();

    std::cout << "Weight(kg): ";
    std::cin >> weight;
    std::cin.ignore();

    currentUser = User(name, age, gender, height, weight);
    userDB->addItem(currentUser);
    userDB->save();
    userExists = true;
    std::cout << "User record saved.\n\n";
}

void Menu::showMainMenu() {
    int choice;
    do {
        std::cout << "1. Configure Profile\n";
        std::cout << "2. Log Meals\n";
        std::cout << "3. Nutritional Insights\n";
        std::cout << "4. View Meal History\n";
        std::cout << "5. Exit\n";
        std::cout << "Enter command (1-5): ";

        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: showProfileMenu(); break;
            case 2: logMeal(); break;
            case 3: generateReport(); break;
            case 4: viewMealHistory(); break;
            case 5:
                std::cout << "\nStart Tracking → Start Shining. Goodbye, " << currentUser.getName() << "!\n";
                saveAllDatabases();
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (true);
}

void Menu::showProfileMenu() {
    int choice;
    do {
        std::cout << "\nProfile Configuration\n";
        std::cout << "1. Name\n";
        std::cout << "2. Age\n";
        std::cout << "3. Gender\n";
        std::cout << "4. Height\n";
        std::cout << "5. Weight\n";
        std::cout << "6. Exit\n";
        std::cout << "Enter command (1-6): ";

        std::cin >> choice;
        std::cin.ignore();

        switch (choice) {
            case 1: {
                std::string name;
                std::cout << "Name: ";
                std::getline(std::cin, name);
                currentUser.setName(name);
                break;
            }
            case 2: {
                int age;
                std::cout << "Age: ";
                std::cin >> age;
                currentUser.setAge(age);
                break;
            }
            case 3: {
                char gender;
                std::cout << "Gender(F/M): ";
                std::cin >> gender;
                gender = std::toupper(gender);
                currentUser.setGender(gender);
                break;
            }
            case 4: {
                double height;
                std::cout << "Height(cm): ";
                std::cin >> height;
                currentUser.setHeight(height);
                break;
            }
            case 5: {
                double weight;
                std::cout << "Weight(kg): ";
                std::cin >> weight;
                currentUser.setWeight(weight);
                break;
            }
            case 6:
                updateUser();
                return;
            default:
                std::cout << "Invalid choice. Please try again.\n";
        }
    } while (true);
}

void Menu::updateUser() {
    auto& users = const_cast<std::vector<User>&>(userDB->getAllItems());
    if (!users.empty()) {
        users[0] = currentUser;
    } else {
        userDB->addItem(currentUser);
    }
    userDB->save();
    std::cout << "User database saved.\n";
}

void Menu::logMeal() {
    std::cout << "\nLog a Meal\n";
    Food food = getFoodFromUser();
    double weight;
    std::cout << "Food weight (g): ";
    std::cin >> weight;
    std::cin.ignore();

    addDietRecord(food, weight);
    std::cout << "Diet record saved.\n\n";
}

Food Menu::getFoodFromUser() {
    char categoryChar;
    std::string categoryStr;
    std::cout << "Select a category (S/A/V/F/B): ";
    std::cin >> categoryChar;
    categoryChar = std::toupper(categoryChar);
    std::cin.ignore();

    const std::string validChars = "SAVFB";
    if (validChars.find(categoryChar) == std::string::npos) {
        std::cout << "Invalid input. Please enter S, A, V, F, or B.\n";
        return getFoodFromUser();
    }

    std::map<char, std::string> categoryMap = {
        {'S', "Staple Food"},
        {'A', "Animal Proteins"},
        {'V', "Vegetables"},
        {'F', "Fruits"},
        {'B', "Beverages"}
    };
    categoryStr = categoryMap[categoryChar];

    std::string foodName;
    std::cout << "Food name: ";
    std::getline(std::cin, foodName);

    auto foods = foodDB->findItems([&](const Food& f) {
        return f.getName() == foodName &&
               Food::categoryToString(f.getCategory()) == categoryStr;
    });

    if (!foods.empty()) {
        return foods[0];
    }

    std::cout << foodName << " is not in the food database.\n";
    double calories;
    std::cout << "Enter calories per 100g (kcal/100g): ";
    std::cin >> calories;
    std::cin.ignore();

    Food newFood(foodName, calories, Food::stringToCategory(categoryStr));
    foodDB->addItem(newFood);
    foodDB->save();
    std::cout << "Food record saved.\n";

    return newFood;
}

void Menu::addDietRecord(const Food& food, double weight) {
    DietRecord record(currentDate, food, weight);
    dietRecordDB->addItem(record);
    dietRecordDB->save();
}

void Menu::generateReport() {
    auto todayRecords = dietRecordDB->findItems([&](const DietRecord& r) {
        return r.getDate() == currentDate;
    });

    double totalCalories = 0.0;
    std::map<FoodCategory, double> categoryWeights;

    for (const auto& record : todayRecords) {
        totalCalories += record.getCalories();
        categoryWeights[record.getFood().getCategory()] += record.getWeight();
    }

    std::ostringstream report;
    report << "Daily Diet Analysis Report (" << currentDate.toString() << ")\n\n";
    report << "Name: " << currentUser.getName() << "\n";
    report << "Age: " << currentUser.getAge() << "\n";
    report << "Gender: " << (currentUser.getGender() == 'M' ? "Male" : "Female") << "\n";
    report << "Height(cm): " << currentUser.getHeight() << "\n";
    report << "Weight(kg): " << currentUser.getWeight() << "\n";
    report << "BMI: " << std::fixed << std::setprecision(1) << currentUser.calculateBMI() << "\n";
    report << "Physical Status: " << currentUser.getBMICategory() << "\n\n";

    report << "Total Calories: " << totalCalories << "\n";
    for (std::map<FoodCategory, double>::const_iterator it = categoryWeights.begin(); it != categoryWeights.end(); ++it) {
        report << Food::categoryToString(it->first) << ": " << it->second << "g\n";
    }

    std::cout << "\n" << report.str() << "\n";

    std::ofstream file("reports/diet_report.txt");
    if (file.is_open()) {
        file << report.str();
        file.close();
        std::cout << "Report saved to diet_report.txt\n";
    } else {
        std::cerr << "Error: Could not save report to file.\n";
    }
}

void Menu::viewMealHistory() {
    std::string dateStr;
    std::cout << "Enter date (yyyy/mm/dd): ";
    std::getline(std::cin, dateStr);

    try {
        Date queryDate(dateStr);
        auto records = dietRecordDB->findItems([&](const DietRecord& r) {
            return r.getDate() == queryDate;
        });

        if (records.empty()) {
            std::cout << "No dietary records found for " << dateStr << ".\n";
            return;
        }

        std::cout << "\nDiet Records for " << dateStr << ":\n";
        std::cout << std::left << std::setw(15) << "Category"
                  << std::setw(25) << "Food Name"
                  << std::setw(10) << "Weight(g)"
                  << "Calories(kcal)\n";
        std::cout << std::string(60, '-') << "\n";

        for (const auto& record : records) {
            std::cout << std::setw(15) << Food::categoryToString(record.getFood().getCategory())
                      << std::setw(25) << record.getFood().getName()
                      << std::setw(10) << record.getWeight()
                      << record.getCalories() << "\n";
        }
        std::cout << "\n";
    } catch (...) {
        std::cout << "Invalid date format. Please use yyyy/mm/dd.\n";
    }
}

void Menu::saveAllDatabases() {
    userDB->save();
    foodDB->save();
    dietRecordDB->save();
}
