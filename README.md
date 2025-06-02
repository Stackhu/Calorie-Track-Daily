# OOP大作业: 每日摄入热量统计系统

## 运行示例: 
###          编译命令: 
```          cd code 
             g++ *.cpp -o a.exe
             ./a.exe
```
###          首次进入程序会提示输入个人信息, 并自动创建data和reports文件夹
###          data包含user.csv, food_database.csv, diet_record.csv
###          reports包含diet_report.txt, 记录饮食报告
###          后续启动程序展示菜单界面, 可根据提示使用相应功能



## Calorie Track Daily 项目文档

---

## 类图

```plaintext
+-------------------+
|       Menu        |
+-------------------+
| - userDB: UserDB* |
| - foodDB: FoodDB* |
| - dietDB: DietDB* |
| - currentUser     |
| - currentDate     |
| - userExists      |
+-------------------+
| + run()           |
| + showMainMenu()  |
| + showWelcome()   |
| + loadOrCreate()  |
| + logMeal()       |
| + generateReport()|
| + viewMealHistory()|
+-------------------+

+-------------------+
|   Database<T>     | <template>
+-------------------+
| - filename        |
| - items: vector<T>|
+-------------------+
| + load()          |
| + save()          |
| + addItem()       |
| + findItems()     |
| + getAllItems()   |
| # parseCSVLine()  |
| # toCSVLine()     |
| # getCSVHeader()  |
+-------------------+

+------------+  +-------------+  +-------------------+
| User       |  | Food        |  | DietRecord        |
+------------+  +-------------+  +-------------------+
| - name     |  | - name      |  | - date            |
| - age      |  | - calories  |  | - food            |
| - gender   |  | - category  |  | - weight          |
| - height   |  +-------------+  | - calories        |
| - weight   |                   +-------------------+
+------------+

+-------------+
| Utils       |
+-------------+
| + split()   |
| + trim()    |
| + fileExists()|
+-------------+
```

---

## 功能模块划分

- **Menu模块**  
  管理程序主流程，包含显示欢迎界面、用户信息、主菜单、食物日志、报告生成等功能。

- **Database模块**  
  泛型数据库模板，支持加载、保存、查找。包含特化类：  
  - UserDatabase  
  - FoodDatabase  
  - DietRecordDatabase  

- **数据类模块**  
  - User：用户信息与指标计算（BMI/BMR）。  
  - Food：食物信息及分类。  
  - DietRecord：单次饮食记录。  

- **Utils模块**  
  提供字符串处理、文件检测等辅助功能。

---

## 关键代码解释

### 目录创建（Windows专用）

```cpp
system("if not exist data mkdir data");
system("if not exist reports mkdir reports");
```

### 首次启动检测与录入
```cpp
userDB->load();
if (userDB->getAllItems().empty()) {
    loadOrCreateUser();
} else {
    currentUser = userDB->getAllItems()[0];
}
```

### 数据文件加载（无警告 + 自动创建空文件）
```cpp
if (!file.is_open()) {
    std::ofstream newFile(filename);
    if (newFile.is_open()) {
        newFile << getCSVHeader() << std::endl;
        newFile.close();
    }
    return;
}
```

### 报告生成
```cpp
for (const auto& record : todayRecords) {
    totalCalories += record.getCalories();
    categoryWeights[record.getFood().getCategory()] += record.getWeight();
}
std::ofstream file("reports/diet_report.txt");
file << report.str();
```

---

## 进一步完善建议

- **多用户支持**  
  实现登录/注册，管理多个用户数据。

- **数据可视化**  
  增加图表显示（柱状图、饼图）以直观展示每日摄入。

- **个性化推荐**  
  根据用户数据（性别、年龄、体重、活动量）生成饮食计划和热量建议。

- **代码优化**  
  使用智能指针（`std::unique_ptr`），增加异常处理，减少资源泄漏。

- **图形界面**  
  将命令行版升级为图形化界面（可用 Qt、C# WinForms）。

---

## 总结
本项目实现了基础的 **每日热量追踪与分析**，可用于学习 C++ 类设计、模板使用、数据持久化。进一步优化可提升实用性和用户体验。
