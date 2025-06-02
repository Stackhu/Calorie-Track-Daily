#ifndef MENU_H
#define MENU_H

#include "User.h"
#include "Date.h"
#include "Food.h" 

#include <string>

// 前向声明
class UserDatabase;
class FoodDatabase;
class DietRecordDatabase;

class Menu {
public:
    Menu();
    void run();

private:
    UserDatabase* userDB;
    FoodDatabase* foodDB;
    DietRecordDatabase* dietRecordDB;

    User currentUser;
    Date currentDate;
    bool userExists;

    void showWelcomeScreen();
    void loadOrCreateUser();
    void showMainMenu();
    void showProfileMenu();
    void logMeal();
    void generateReport();
    void viewMealHistory();

    void updateUser();
    void addDietRecord(const Food& food, double weight);
    Food getFoodFromUser();
    void saveAllDatabases();
};

#endif
