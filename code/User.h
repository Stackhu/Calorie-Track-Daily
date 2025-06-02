#ifndef USER_H
#define USER_H

#include <string>

class User {
public:
    User();
    User(const std::string& name, int age, char gender, double height, double weight);
    
    // 计算用户指标
    double calculateBMI() const;
    double calculateBMR() const;  // 基础代谢率
    double calculateDailyCalories() const;  // 每日建议摄入量
    
    // BMI分类
    std::string getBMICategory() const;
    
    // 访问器
    std::string getName() const;
    int getAge() const;
    char getGender() const;
    double getHeight() const;
    double getWeight() const;
    
    // 修改器
    void setName(const std::string& name);
    void setAge(int age);
    void setGender(char gender);
    void setHeight(double height);
    void setWeight(double weight);
    
private:
    std::string name;
    int age;
    char gender;  // 'M' or 'F'
    double height; // cm
    double weight; // kg
};

#endif // USER_H