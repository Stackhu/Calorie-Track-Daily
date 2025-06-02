#include "Database.h"
#include "Date.h"
#include "DietRecord.h"
#include "Food.h"
#include "Menu.h"
#include "User.h"
#include "Utils.h"

#include <ctime>
#include <sstream>
#include <iomanip>
#include <stdexcept>

Date::Date() {
    time_t now = time(nullptr);
    tm* local_time = localtime(&now);
    year = local_time->tm_year + 1900;
    month = local_time->tm_mon + 1;
    day = local_time->tm_mday;
}

Date::Date(int year, int month, int day) 
    : year(year), month(month), day(day) {}

Date::Date(const std::string& dateStr) {
    char delimiter;
    std::istringstream ss(dateStr);
    ss >> year >> delimiter >> month >> delimiter >> day;
}

int Date::getYear() const { return year; }
int Date::getMonth() const { return month; }
int Date::getDay() const { return day; }

std::string Date::toString() const {
    std::ostringstream oss;
    oss << year << '/' 
        << std::setfill('0') << std::setw(2) << month << '/' 
        << std::setfill('0') << std::setw(2) << day;
    return oss.str();
}

bool Date::operator==(const Date& other) const {
    return year == other.year && month == other.month && day == other.day;
}

bool Date::operator<(const Date& other) const {
    if (year != other.year) return year < other.year;
    if (month != other.month) return month < other.month;
    return day < other.day;
}