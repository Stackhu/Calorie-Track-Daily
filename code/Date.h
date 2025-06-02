#ifndef DATE_H
#define DATE_H

#include <ctime>
#include <string>

class Date {
public:
    Date();  // 默认构造函数（当前日期）
    Date(int year, int month, int day);
    Date(const std::string& dateStr);  // 从"yyyy/mm/dd"字符串构造
    
    // 获取日期信息
    int getYear() const;
    int getMonth() const;
    int getDay() const;
    
    // 日期操作
    std::string toString() const;
    bool operator==(const Date& other) const;
    bool operator<(const Date& other) const;
    
private:
    int year;
    int month;
    int day;
};

#endif // DATE_H