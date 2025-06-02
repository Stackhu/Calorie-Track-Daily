#ifndef DATABASE_H
#define DATABASE_H

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <fstream>

#include "Date.h"
#include "Menu.h"
#include "Utils.h"
#include "User.h"
#include "Food.h"
#include "DietRecord.h"

template <typename T>
class Database {
public:
    Database(const std::string& filename) : filename(filename) {}
    virtual ~Database() = default;

    void load() {
        items.clear();
        std::ifstream file(filename);
        if (!file.is_open()) {
            // 文件不存在，自动创建空文件
            std::ofstream newFile(filename);
            if (newFile.is_open()) {
                newFile << getCSVHeader() << std::endl;
                newFile.close();
            }
            return; // 不输出warning
        }

        std::string line;
        if (std::getline(file, line)) {
            while (std::getline(file, line)) {
                if (!line.empty()) {
                    try {
                        items.push_back(parseCSVLine(line));
                    } catch (const std::exception&) {
                        // 忽略解析错误
                    }
                }
            }
        }
        file.close();
    }

    void save() const {
        std::ofstream file(filename);
        if (!file.is_open()) {
            std::cerr << "Error: Could not open file " << filename << " for writing." << std::endl;
            return;
        }

        file << getCSVHeader() << std::endl;
        for (const auto& item : items) {
            file << toCSVLine(item) << std::endl;
        }
        file.close();
    }

    void addItem(const T& item) {
        items.push_back(item);
    }

    std::vector<T> findItems(std::function<bool(const T&)> predicate) const {
        std::vector<T> results;
        for (const auto& item : items) {
            if (predicate(item)) {
                results.push_back(item);
            }
        }
        return results;
    }

    const std::vector<T>& getAllItems() const {
        return items;
    }

protected:
    virtual T parseCSVLine(const std::string& line) const = 0;
    virtual std::string toCSVLine(const T& item) const = 0;
    virtual std::string getCSVHeader() const = 0;

    std::string filename;
    std::vector<T> items;
};

class UserDatabase : public Database<User> {
public:
    UserDatabase(const std::string& filename) : Database<User>(filename) {}

protected:
    User parseCSVLine(const std::string& line) const override;
    std::string toCSVLine(const User& item) const override;
    std::string getCSVHeader() const override;
};

class FoodDatabase : public Database<Food> {
public:
    FoodDatabase(const std::string& filename) : Database<Food>(filename) {}

protected:
    Food parseCSVLine(const std::string& line) const override;
    std::string toCSVLine(const Food& item) const override;
    std::string getCSVHeader() const override;
};

class DietRecordDatabase : public Database<DietRecord> {
public:
    DietRecordDatabase(const std::string& filename) : Database<DietRecord>(filename) {}

protected:
    DietRecord parseCSVLine(const std::string& line) const override;
    std::string toCSVLine(const DietRecord& item) const override;
    std::string getCSVHeader() const override;
};

#endif // DATABASE_H
