#include "Database.h"
#include "Date.h"
#include "DietRecord.h"
#include "Food.h"
#include "Menu.h"
#include "User.h"
#include "Utils.h"

int main() {
    // 确保报告目录存在
    system("if not exist reports mkdir reports");

    Menu app;
    app.run();
    return 0;
}
